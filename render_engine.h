#ifndef _INCLUDE_RENDER_ENGINE_H_
#define _INCLUDE_RENDER_ENGINE_H_

#include "typedefs.h"
#include "vector3.h"
#include "vector4.h"
#include "color_rgb.h"
#include "set.h"
#include "sun_light.h"
#include "mesh.h"

namespace gfx{
class render_engine{
public:
    
    struct uvector2{
        utype y,x;
        uvector2() {}
        uvector2(utype py,utype px) : y(py), x(px) {}
    };
    
    //buffers
    vector4 *rgbz_buffer=nullptr,*vertex_buffer=nullptr;
    uvector2 *vertex_screen_buffer=nullptr;
    utype rgbz_buffer_size=0, vertex_buffer_size=0;
    
    render_engine();
    render_engine(utype vbuf);
    render_engine(utype height,utype width);
    render_engine(utype height,utype width, utype vbuf);
    ~render_engine();
    
    //buffer handling
    inline void resize_rgbz(utype size);
    inline void resize_rgbz(utype height,utype width);
    inline void upsize_rgbz(utype size);
    inline void upsize_rgbz(utype height,utype width);
    inline void delete_rgbz();
    
    inline void resize_vertex(utype size);
    inline void upsize_vertex(utype size);
    inline void delete_vertex();
    
    inline void delete_buffers();
    
    //render!!!!!!
    void render(const set::set_pointer scene,int *out_buffer,utype YRES,utype XRES,const transformator& camera,color_rgb ambient_light,const color_rgb &background_color,sun_light sun);
private:
    inline void _render_scene_meshes(const set* grp,utype &YRES,utype &XRES,const transformator& camera,color_rgb &ambient_light,sun_light &sun);
    inline void _render_mesh(const mesh& m,utype &YRES,utype &XRES,const transformator& T,color_rgb &ambient_light,sun_light &sun);//TODO
};
};

#endif
