#include "render_engine_parallel.h"
#include <stack>
#include <limits>
#include <cassert>
#include <omp.h>

//#define _BOUNDING_BOXES_ 1

namespace gfx{

render_engine_parallel::render_engine_parallel(utype width,utype height) : YRES(height),XRES(width),YXRES(height*width),T(omp_get_max_threads()) {
    for(int i=0;i<T;i++)rgbz_buffer[i]=new vector4 [YXRES];
    utype chunksize=YXRES/T;
    std::cout<<T<<" threads available"<<std::endl;
    _end[0]=chunksize;
    for(int i=1;i<T;i++){_start[i]=_end[i-1];_end[i]=_start[i]+chunksize;}
    _end[T-1]=YXRES;
}
render_engine_parallel::render_engine_parallel(utype width,utype height, utype vbuf)  : YRES(height),XRES(width),YXRES(height*width),T(omp_get_max_threads()) {
    for(int i=0;i<T;i++)rgbz_buffer[i]=new vector4 [YXRES];
    resize_vertex(vbuf);
    std::cout<<T<<" threads available"<<std::endl;
    utype chunksize=YXRES/T;
    _end[0]=chunksize;
    for(int i=1;i<T;i++){_start[i]=_end[i-1];_end[i]=_start[i]+chunksize;}
    _end[T-1]=YXRES;
}
render_engine_parallel::~render_engine_parallel() {delete_vertex();for(int i=0;i<T;i++)delete[] rgbz_buffer[i];}

//buffer handling
void render_engine_parallel::resize_vertex(utype size){
    delete_vertex();
    if(size>0){
        vertex_buffer = new vector4 [size];
        vertex_screen_buffer = new uvector2 [size];
        vertex_buffer_size = size;
    }
}
void render_engine_parallel::upsize_vertex(utype size){
    if(size>vertex_buffer_size)resize_vertex(size);
}
void render_engine_parallel::delete_vertex() {
    if(vertex_buffer_size){delete[] vertex_buffer;delete[] vertex_screen_buffer;}
    vertex_buffer=nullptr;
    vertex_screen_buffer=nullptr;
    vertex_buffer_size=0;
}

void render_engine_parallel::render(const set::set_pointer scene,const camera& cam,color_rgb ambient_light,const color_rgb &background_color,sun_light sun) {

//makes camera invertible so that we can remove it from sunlight
    sun.vector=cam.inverse.apply(sun.vector);
//retrieve variables
    utype YRES = cam.yres,XRES=cam.xres;
    dtype near_clipping = cam.near, far_clipping = cam.far, cam_h = cam.h, cam_w = cam.w;
    dtype mult_factor = ((dtype)YRES)/cam_h;
//enlarge buffers if needed
    utype YXRES = YRES*XRES;
    upsize_vertex(scene->max_sub_vertices());
//initialize rgbz buffer
    #pragma omp parallel
    {   
        utype t_id = omp_get_thread_num();
        std::fill(rgbz_buffer[t_id],rgbz_buffer[t_id]+YXRES,vector4(background_color,std::numeric_limits<dtype>::infinity()));
    }
//process queue

    struct process_node{
        const set* grp;
        transformator T;
        set::set_vector::const_iterator it;
        process_node(const set* g,const transformator& t1) : grp(g),T(t1),it(g->subsets.begin()) {}
        process_node(const set* g,const transformator& t1,const transformator& t2) : grp(g),T(t1,t2),it(g->subsets.begin()) {}
    };
    
    std::stack<process_node> jobs;
    jobs.emplace(scene.get(),cam.inverse);
    while(!jobs.empty()){
        if(jobs.top().it==jobs.top().grp->subsets.end()){
            //render meshes of set jobs.top.grp
            
            for(set::mesh_vector::const_iterator it=jobs.top().grp->meshes.begin();it!=jobs.top().grp->meshes.end();++it)
            {
                transformator T(jobs.top().T,it->first);
                const mesh& m=it->second.operator*();
                //render mesh m
                
                //parallel vertex shading
                vector3 *v=m.v,*vn=m.vn,*vc=m.vc;
                vector4 *rgbz=vertex_buffer;
                uvector2 *yx=vertex_screen_buffer;

                //for(int NV=m.n_vertices;NV--;++v,++vn,++vc,++rgbz,++yx)
                int NV=m.n_vertices;
                #pragma omp parallel for
                for(int i=0;i<NV;i++)
                {
                    vector3 cv=T.apply(v[i]);
                    if(omp_get_thread_num()==0)std::cout<<cv<<" "<<near_clipping<<" "<<far_clipping<<std::endl;
                    if(cv.z<near_clipping || cv.z>far_clipping){yx[i]={invalid_crd,invalid_crd};continue;}
                    putc('.',stderr);
                    vector3 fv(cv.x*near_clipping/cv.z + cam_w/2,cv.y*near_clipping/cv.z + cam_h/2,cv.z);
                    if(fv.x<0 || fv.x>=cam_w || fv.y<0 || fv.y>=cam_h){yx[i]={invalid_crd,invalid_crd};continue;}
                    yx[i]={(utype)(fv.y*mult_factor),(utype)(fv.x*mult_factor)}; assert(yx->y>=0 && yx->y<YRES && yx->x>=0 && yx->x<XRES);    
                    vector3 cvn=T.apply(vn[i]);cvn-=cv;cvn.normalise();
                    rgbz[i]=vector4(vc[i]*(ambient_light+sun.color*std::max<dtype>(sun.vector.dot(cvn),0)),cv.z);
                }
                //triangles shading
                mesh::utype3* ids=m.t;
                
                int NT=m.n_triangles;
                #pragma omp parallel for
                for(int i=0;i<NT;i++)
                {
                    utype t_id = omp_get_thread_num();
                    utype i0=m.t[i].i0,i1=m.t[i].i1,i2=m.t[i].i2;
                    uvector2 yx0=vertex_screen_buffer[i0],yx1=vertex_screen_buffer[i1],yx2=vertex_screen_buffer[i2];
                    if(yx0.x==invalid_crd || yx1.x==invalid_crd || yx2.x==invalid_crd)continue;
                    //if inverted, remove it
                    stype cross = (((int)yx1.x)-((int)yx0.x))*(((int)yx2.y)-((int)yx1.y))-(((int)yx1.y)-((int)yx0.y))*(((int)yx2.x)-((int)yx1.x));
                    //fprintf(stderr,"tri %d(%d,%d) %d(%d,%d) %d(%d,%d) X %d\n",i0,yx0.y,yx0.x,i1,yx1.y,yx1.x,i2,yx2.y,yx2.x,cross);
                    
                    
                    if(cross==0)continue;
                    

                    //shade triangles
                    stype den_x = (((int)yx2.x)-((int)yx0.x))*(((int)yx1.y)-((int)yx0.y))-(((int)yx2.y)-((int)yx0.y))*(((int)yx1.x)-((int)yx0.x));
                    assert(den_x!=0);
                    vector4 rgbz0 = vertex_buffer[i0],rgbz1=vertex_buffer[i1],rgbz2=vertex_buffer[i2];
                    
                    vector4 drgbz_x = (rgbz2-rgbz0)*(((int)yx1.y)-((int)yx0.y)) - (rgbz1-rgbz0)*(((int)yx2.y)-((int)yx0.y));drgbz_x/=den_x;
                    vector4 drgbz_y = (rgbz2-rgbz0)*(((int)yx1.x)-((int)yx0.x)) - (rgbz1-rgbz0)*(((int)yx2.x)-((int)yx0.x));drgbz_y/=(-den_x);
                    
                    
                        
                    //fill triangle
                        //set i0 the smallest
                        if(yx2.y<yx1.y){
                            if(yx2.y<yx0.y){yx0.swap(yx2);rgbz0.swap(rgbz2);}
                        } else if(yx1.y<yx0.y){yx0.swap(yx1);rgbz0.swap(rgbz1);}
                        dtype dx1=(dtype)((int)yx1.x-(int)yx0.x)/((int)yx1.y-(int)yx0.y),
                              dx2=(dtype)((int)yx2.x-(int)yx0.x)/((int)yx2.y-(int)yx0.y);
                        //i1 the leftmost
                        if(dx2<dx1){yx1.swap(yx2);std::swap(dx1,dx2);rgbz1.swap(rgbz2);};
                        
                        /*fprintf(stderr,"tri (%d,%d) (%d,%d) (%d,%d)\n",yx0.y,yx0.x,yx1.y,yx1.x,yx2.y,yx2.x);
                        std::cerr<<rgbz0<<" "<<rgbz1<<" "<<rgbz2<<" "<<std::endl;
                        std::cerr<<"drgbz/dx: "<<drgbz_x<<std::endl;
                        std::cerr<<"drgbz/dy: "<<drgbz_y<<std::endl;*/
                        
                        if(yx1.y<yx2.y)
                        {
                            
#ifdef _BOUNDING_BOXES_
                            //green bounding box
                            {
                                int my=std::min(yx0.y,std::min(yx1.y,yx2.y));
                                int My=std::max(yx0.y,std::max(yx1.y,yx2.y));
                                int mx=std::min(yx0.x,std::min(yx1.x,yx2.x));
                                int Mx=std::max(yx0.x,std::max(yx1.x,yx2.x));
                                for(int y=my;y<=My;y++)for(int x=mx;x<=Mx;x++)if(std::numeric_limits<dtype>::max()<rgbz_buffer[y*XRES+x].w)rgbz_buffer[y*XRES+x]=vector4(0,10,0,std::numeric_limits<dtype>::max());
                            }
#endif
                            
                            //(0->1)(0->2);
                            dtype dsx=yx0.x,dex=yx0.x;
                            utype usx=yx0.x;vector4 csx=rgbz0;
                            vector4 *vsb=rgbz_buffer[t_id]+yx0.y*XRES+usx;
                            for(int y=yx0.y;y<=yx1.y;y++,dsx+=dx1,dex+=dx2,csx+=drgbz_y,vsb+=XRES)
                            {
                                //shift u
                                utype idsx=(utype)dsx,idex=(utype)dex;
                                //fprintf(stderr,"%d] [%d %d]\n",y,idsx,idex);
                                while(usx>idsx){--usx;csx-=drgbz_x;--vsb;}
                                while(usx<idsx){++usx;csx+=drgbz_x;++vsb;}
                                vector4 tb(csx);
                                vector4* vb(vsb);//(rgbz_buffer+y*XRES+idsx);
                                for(int x=idsx;x<=idex;x++,tb+=drgbz_x,vb++)
                                {
                                    //put pixel
                                    //if(tb.w<rgbz_buffer[y*XRES+x].w)rgbz_buffer[y*XRES+x]=tb;
                                    if(tb.w<vb->w)*vb=tb;
                                }
                                if(y==yx1.y)break;
                            }
                            //(1->2)(0->2);
                            dtype dx12=(dtype)((int)yx2.x-(int)yx1.x)/((int)yx2.y-(int)yx1.y);
                            dsx=yx1.x;
                            csx=rgbz1;
                            //TODO: remove following two lines, maybe unnecessary
                            usx=yx1.x;
                            vsb=rgbz_buffer[t_id]+yx1.y*XRES+usx;
                            for(int y=yx1.y;y<=yx2.y;y++,dsx+=dx12,dex+=dx2,csx+=drgbz_y,vsb+=XRES)
                            {
                                //shift u
                                utype idsx=(utype)dsx,idex=(utype)dex;
                                //fprintf(stderr,"%d] [%d %d]\n",y,idsx,idex);
                                while(usx>idsx){--usx;csx-=drgbz_x;--vsb;}
                                while(usx<idsx){++usx;csx+=drgbz_x;++vsb;}
                                vector4 tb(csx);
                                vector4* vb(vsb);//(rgbz_buffer+y*XRES+idsx);
                                for(int x=idsx;x<=idex;x++,tb+=drgbz_x,vb++)
                                {
                                    //put pixel
                                    //if(tb.w<rgbz_buffer[y*XRES+x].w)rgbz_buffer[y*XRES+x]=tb;
                                    if(tb.w<vb->w)*vb=tb;
                                }
                                if(y==yx2.y)break;
                            }
                        }
                        else
                        {
#ifdef _BOUNDING_BOXES_                    
                            //red bounding box
                            {
                                int my=std::min(yx0.y,std::min(yx1.y,yx2.y));
                                int My=std::max(yx0.y,std::max(yx1.y,yx2.y));
                                int mx=std::min(yx0.x,std::min(yx1.x,yx2.x));
                                int Mx=std::max(yx0.x,std::max(yx1.x,yx2.x));
                                for(int y=my;y<=My;y++)for(int x=mx;x<=Mx;x++)if(std::numeric_limits<dtype>::max()<rgbz_buffer[y*XRES+x].w)rgbz_buffer[y*XRES+x]=vector4(10,0,0,std::numeric_limits<dtype>::max());
                            }
#endif
                            //right ends
                            //(0->1)(0->2);
                            dtype dsx=yx0.x,dex=yx0.x;
                            utype usx=yx0.x;vector4 csx=rgbz0;
                            vector4 *vsb=rgbz_buffer[t_id]+yx0.y*XRES+usx;
                            for(int y=yx0.y;y<=yx2.y;y++,dsx+=dx1,dex+=dx2,csx+=drgbz_y,vsb+=XRES)
                            {
                                
                                //shift u
                                utype idsx=(utype)dsx,idex=(utype)dex;
                                //fprintf(stderr,"%d] [%d %d]",y,idsx,idex);std::cerr<<csx<<std::endl;
                                while(usx>idsx){--usx;csx-=drgbz_x;--vsb;}
                                while(usx<idsx){++usx;csx+=drgbz_x;++vsb;}
                                vector4 tb(csx);
                                vector4* vb(vsb);//(rgbz_buffer+y*XRES+idsx);
                                for(int x=idsx;x<=idex;x++,tb+=drgbz_x,vb++)
                                {
                                    //put pixel
                                    //if(tb.w<rgbz_buffer[y*XRES+x].w)rgbz_buffer[y*XRES+x]=tb;
                                    if(tb.w<vb->w)*vb=tb;
                                }
                                if(y==yx2.y)break;
                            }
                            //(0->1)(2->1);
                            dtype dx21=(dtype)((int)yx2.x-(int)yx1.x)/((int)yx2.y-(int)yx1.y);
                            dex=yx2.x;
                            //usx=yx2.x;
                            for(int y=yx2.y;y<=yx1.y;y++,dsx+=dx1,dex+=dx21,csx+=drgbz_y,vsb+=XRES)
                            {
                                //shift u
                                utype idsx=(utype)dsx,idex=(utype)dex;
                                //fprintf(stderr,"%d] [%d %d]\n",y,idsx,idex);
                                while(usx>idsx){--usx;csx-=drgbz_x;--vsb;}
                                while(usx<idsx){++usx;csx+=drgbz_x;++vsb;}
                                vector4 tb(csx);
                                vector4* vb(vsb);//(rgbz_buffer+y*XRES+idsx);
                                for(int x=idsx;x<=idex;x++,tb+=drgbz_x,vb++)
                                {
                                    //put pixel
                                    //if(tb.w<rgbz_buffer[y*XRES+x].w)rgbz_buffer[y*XRES+x]=tb;
                                    if(tb.w<vb->w)*vb=tb;
                                }
                                if(y==yx1.y)break;
                            }
                        }
                        
                //putc('-',stderr);
                }
            }
            //putc('#',stderr);
            //putc(10,stderr);
            
            jobs.pop();
        }
        else{
            set::set_vector::const_iterator it = jobs.top().it++;
            jobs.emplace(it->second.get(),jobs.top().T,it->first);
        }
    }

    /*int *c_buf=cam.video_buffer;
//translate rgbz_buffer on out_buffer
    #pragma omp parallel
    {   
        utype t_id = omp_get_thread_num();
        utype s=_start[t_id],e=_end[t_id];
        int *out_buffer=c_buf+s;
        for(int i=s;i<e;i++,out_buffer++)
        {
            int n=0;
            for(int j=1;j<T;j++)if(rgbz_buffer[j][i].w<rgbz_buffer[n][i].w)n=j;
            *out_buffer=rgbz_buffer[n][i].int_tonemap();
        }
        printf("%d done!\n",t_id);
    }*/
    int *out_buffer=cam.video_buffer;
    for(vector4* v=rgbz_buffer[0];YXRES--;++v,++out_buffer)*out_buffer=v->int_tonemap();
    
}
    
};
