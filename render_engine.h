#ifndef _INCLUDE_RENDER_ENGINE_H_
#define _INCLUDE_RENDER_ENGINE_H_

#include "typedefs.h"
#include "vector3.h"
#include "vector4.h"
#include "color_rgb.h"

namespace gfx{
class render_engine{
    //buffers
    vector4 *rgbz_buffer=nullptr,*vertex_buffer=nullptr;
    utype rgbz_buffer_size=0, vertex_buffer_size=0;
    
    render_engine();
    render_engine(utype vbuf);
    render_engine(utype height,utype width);
    render_engine(utype height,utype width, utype vbuf);
    ~render_engine();
    
    //buffer handling
    void resize_rgbz(utype size);
    void resize_rgbz(utype height,utype width);
    void upsize_rgbz(utype size);
    void upsize_rgbz(utype height,utype width);
    void delete_rgbz();
    
    void resize_vertex(utype size);
    void upsize_vertex(utype size);
    void delete_vertex();
    
    void delete_buffers();
    
};
};

#endif
