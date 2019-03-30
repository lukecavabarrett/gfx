#include "mesh.h"

namespace gfx{

utype mesh::_id_mesh_counter_=0;
    
mesh::mesh() : id(++_id_mesh_counter_), name("empty_mesh") {
    
    n_vertices=n_triangles=0;
    v=vn=vc=nullptr;
    t=nullptr;
}

mesh::mesh(basic_shape shape) : id(++_id_mesh_counter_) {
switch(shape) {
case basic_shape::cube:
    name = std::string("basic_cube");
    n_vertices=24;
    n_triangles=12;
    t = new utype3 [n_triangles];
    v = new vector3 [n_vertices];
    vn = new vector3 [n_vertices];
    vc = new color_rgb [n_vertices];
    //X+
    v[0]=vector3(0.5,0.5,0.5);
    v[1]=vector3(0.5,-0.5,0.5);
    v[2]=vector3(0.5,-0.5,-0.5);
    v[3]=vector3(0.5,0.5,-0.5);
    vn[0]=vn[1]=vn[2]=vn[3]=vector3(1,0,0);
    t[0]={0,1,2};
    t[1]={2,3,0};
    //X-
    v[4]=vector3(-0.5,0.5,0.5);
    v[5]=vector3(-0.5,-0.5,0.5);
    v[6]=vector3(-0.5,-0.5,-0.5);
    v[7]=vector3(-0.5,0.5,-0.5);
    vn[4]=vn[5]=vn[6]=vn[7]=vector3(-1,0,0);
    t[2]={4,5,6};
    t[3]={6,7,4};
    //Y+
    v[8]=vector3(0.5,0.5,0.5);
    v[9]=vector3(-0.5,0.5,0.5);
    v[10]=vector3(-0.5,0.5,-0.5);
    v[11]=vector3(0.5,0.5,-0.5);
    vn[8]=vn[9]=vn[10]=vn[11]=vector3(0,1,0);
    t[4]={8,9,10};
    t[5]={10,11,8};
    //Y-
    v[12]=vector3(0.5,-0.5,0.5);
    v[13]=vector3(-0.5,-0.5,0.5);
    v[14]=vector3(-0.5,-0.5,-0.5);
    v[15]=vector3(0.5,-0.5,-0.5);
    vn[12]=vn[13]=vn[14]=vn[15]=vector3(0,-1,0);
    t[6]={12,13,14};
    t[7]={14,15,12};
    //Z+
    v[16]=vector3(0.5,0.5,0.5);
    v[17]=vector3(0.5,-0.5,0.5);
    v[18]=vector3(-0.5,-0.5,0.5);
    v[19]=vector3(-0.5,0.5,0.5);
    vn[16]=vn[17]=vn[18]=vn[19]=vector3(0,0,1);
    t[8]={16,17,18};
    t[9]={18,19,20};
    //Z-
    v[20]=vector3(0.5,0.5,-0.5);
    v[21]=vector3(0.5,-0.5,-0.5);
    v[22]=vector3(-0.5,-0.5,-0.5);
    v[23]=vector3(-0.5,0.5,-0.5);
    t[10]={20,21,22};
    t[11]={22,23,20};
    
    vn[20]=vn[21]=vn[22]=vn[23]=vector3(0,0,-1);
    for(int i=0;i<n_vertices;i++)vc[i]=color_rgb(0.4);
    for(int i=0;i<n_vertices;i++)vn[i]+=v[i];
    
    //X+
    t[0]={0,1,2};
    t[1]={2,3,1};

    //X-
    v[4]=vector3(-0.5,0.5,0.5);
    v[5]=vector3(-0.5,-0.5,0.5);
    v[6]=vector3(-0.5,-0.5,-0.5);
    v[7]=vector3(-0.5,0.5,-0.5);
    vn[4]=vn[5]=vn[6]=vn[7]=vector3(-1,0,0);
    //Y+
    v[8]=vector3(0.5,0.5,0.5);
    v[9]=vector3(-0.5,0.5,0.5);
    v[10]=vector3(-0.5,0.5,-0.5);
    v[11]=vector3(0.5,0.5,-0.5);
    vn[8]=vn[9]=vn[10]=vn[11]=vector3(0,1,0);
    //Y-
    v[12]=vector3(0.5,-0.5,0.5);
    v[13]=vector3(-0.5,-0.5,0.5);
    v[14]=vector3(-0.5,-0.5,-0.5);
    v[15]=vector3(0.5,-0.5,-0.5);
    vn[12]=vn[13]=vn[14]=vn[15]=vector3(0,-1,0);
    //Z+
    v[16]=vector3(0.5,0.5,0.5);
    v[17]=vector3(0.5,-0.5,0.5);
    v[18]=vector3(-0.5,-0.5,0.5);
    v[19]=vector3(-0.5,0.5,0.5);
    vn[16]=vn[17]=vn[18]=vn[19]=vector3(0,0,1);
    //Z-
    v[20]=vector3(0.5,0.5,-0.5);
    v[21]=vector3(0.5,-0.5,-0.5);
    v[22]=vector3(-0.5,-0.5,-0.5);
    v[23]=vector3(-0.5,0.5,-0.5);
    
break;


default:
throw std::runtime_error("Did you really think I had the time for implementing a tethraedron? (or sphere, monkey, broccoli, etc...)");
break;
}
}

mesh::mesh(const char* filename) : id(++_id_mesh_counter_),name(filename) {
    throw std::runtime_error("I haven't implemented that yet");
}

mesh::~mesh(){
    fprintf(stderr,"destroying mesh with %d vertices and %d triangles\n",n_vertices,n_triangles);
    if(n_vertices){
        delete[] v;
        delete[] vn;
        delete[] vc;
    }
    if(n_triangles){
        delete[] t;
    }
}


    
};
