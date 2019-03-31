#include "render_engine.h"
#include <stack>
#include <limits>

namespace gfx{
    
render_engine::render_engine() {}
render_engine::render_engine(utype vbuf) {resize_vertex(vbuf);}
render_engine::render_engine(utype height,utype width) {resize_rgbz(height,width);}
render_engine::render_engine(utype height,utype width, utype vbuf) {resize_rgbz(height,width);resize_vertex(vbuf);}
render_engine::~render_engine() {delete_buffers();}

//buffer handling
void render_engine::resize_rgbz(utype size){
    delete_rgbz();
    if(size>0){
        rgbz_buffer = new vector4 [size];
        rgbz_buffer_size = size;
    }
}
void render_engine::resize_rgbz(utype height,utype width){
    resize_rgbz(height*width);
}
void render_engine::upsize_rgbz(utype size){
    if(size>rgbz_buffer_size)resize_rgbz(size);
}
void render_engine::upsize_rgbz(utype height,utype width) {
    upsize_rgbz(height*width);
}

void render_engine::delete_rgbz(){
    if(rgbz_buffer_size)delete[] rgbz_buffer;
    rgbz_buffer=nullptr;
    rgbz_buffer_size=0;
}

void render_engine::resize_vertex(utype size){
    delete_vertex();
    if(size>0){
        vertex_buffer = new vector4 [size];
        vertex_screen_buffer = new uvector2 [size];
        vertex_buffer_size = size;
    }
}
void render_engine::upsize_vertex(utype size){
    if(size>vertex_buffer_size)resize_vertex(size);
}
void render_engine::delete_vertex() {
    if(vertex_buffer_size){delete[] vertex_buffer;delete[] vertex_screen_buffer;}
    vertex_buffer=nullptr;
    vertex_screen_buffer=nullptr;
    vertex_buffer_size=0;
}

void render_engine::delete_buffers() {
    if(rgbz_buffer_size)delete[] rgbz_buffer;
    if(vertex_buffer_size){delete[] vertex_buffer;delete[] vertex_screen_buffer;}
    rgbz_buffer=vertex_buffer=nullptr;
    vertex_screen_buffer=nullptr;
    rgbz_buffer_size=vertex_buffer_size=0;
}


inline void render_engine::_render_mesh(const mesh& m,utype &YRES,utype &XRES,const transformator& T,color_rgb &ambient_light,sun_light &sun){
    //TODO
    //std::cerr<<"rendering "<<m.name<<" with "<<T<<std::endl;
    
    //vertex shading
    {
        vector3 *v=m.v,*vn=m.vn,*vc=m.vc;
        vector4 *rgbz=vertex_buffer;
        uvector2 *yx=vertex_screen_buffer;
        //parallel
        for(int NV=m.n_vertices;NV--;v++,vn++,vc++,rgbz++,yx++)
        {
            vector3 cv=T.apply(*v),cvn=T.apply(*vn);cvn-=cv;cvn.normalise();
            *rgbz=vector4(*vc*(ambient_light+sun.color*sun.vector.dot(cvn)),cv.z);
        }
    }
}

void render_engine::_render_scene_meshes(const set* grp, utype& YRES, utype& XRES, const transformator& camera, color_rgb& ambient_light, sun_light& sun)
{
    for(set::mesh_vector::const_iterator it=grp->meshes.begin();it!=grp->meshes.end();++it)_render_mesh(it->second.operator*(),YRES,XRES,transformator(camera,it->first),ambient_light,sun);
}

void render_engine::render(const set::set_pointer scene,int *out_buffer,utype YRES,utype XRES,const transformator& camera,color_rgb ambient_light,const color_rgb& background_color,sun_light sun) {

    //TODO makes camera invertible so that we can remove it from sunlight
    
//enlarge buffers if needed
    utype YXRES = YRES*XRES;
    upsize_rgbz(YXRES);
    upsize_vertex(scene->max_sub_vertices());
//initialize rgbz buffer
    std::fill(rgbz_buffer,rgbz_buffer+YXRES,vector4(background_color,std::numeric_limits<dtype>::infinity()));
//process queue

    struct process_node{
        const set* grp;
        transformator T;
        set::set_vector::const_iterator it;
        process_node(const set* g,const transformator& t1) : grp(g),T(t1),it(g->subsets.begin()) {}
        process_node(const set* g,const transformator& t1,const transformator& t2) : grp(g),T(t1,t2),it(g->subsets.begin()) {}
    };
    
    std::stack<process_node> jobs;
    jobs.emplace(scene.get(),camera);
    while(!jobs.empty()){
        if(jobs.top().it==jobs.top().grp->subsets.end()){
            _render_scene_meshes(jobs.top().grp,YRES,XRES,camera,ambient_light,sun);
            jobs.pop();
        }
        else{
            set::set_vector::const_iterator it = jobs.top().it++;
            jobs.emplace(it->second.get(),jobs.top().T,it->first);
        }
    }

//translate rgbz_buffer on out_buffer
    for(vector4* v=rgbz_buffer;YXRES--;++v,++out_buffer)*out_buffer=v->int_tonemap();
    
}
    
};
