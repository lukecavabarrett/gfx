#ifndef _INCLUDE_RENDER_ENGINE_H_
#define _INCLUDE_RENDER_ENGINE_H_

#include "typedefs.h"
#include "vector3.h"
#include "vector4.h"
#include "color_rgb.h"
#include "set.h"
#include "sun_light.h"
#include "mesh.h"
#include "camera.h"

namespace gfx{
class render_engine{
public:
    
    static constexpr utype invalid_crd = -1;
    struct uvector2{
        utype y,x;
        uvector2() {}
        uvector2(utype py,utype px) : y(py), x(px) {}
        void swap(uvector2& o){
            utype t;
            t=y;y=o.y;o.y=t;
            t=x;x=o.x;o.x=t;
        }
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
    void render(const set::set_pointer scene,const camera& cam,color_rgb ambient_light,const color_rgb &background_color,sun_light sun);
private:
};
};

#endif
