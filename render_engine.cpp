#include "render_engine.h"

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
        vertex_buffer_size = size;
    }
}
void render_engine::upsize_vertex(utype size){
    if(size>vertex_buffer_size)resize_vertex(size);
}
void render_engine::delete_vertex() {
    if(vertex_buffer_size)delete[] vertex_buffer;
    vertex_buffer=nullptr;
    vertex_buffer_size=0;
}

void render_engine::delete_buffers() {
    if(rgbz_buffer_size)delete[] rgbz_buffer;
    if(vertex_buffer_size)delete[] vertex_buffer;
    rgbz_buffer=vertex_buffer=nullptr;
    rgbz_buffer_size=vertex_buffer_size=0;
}
    
};
