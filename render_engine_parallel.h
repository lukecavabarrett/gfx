#ifndef _INCLUDE_RENDER_ENGINE_PARALLEL_H_
#define _INCLUDE_RENDER_ENGINE_PARALLEL_H_

#include "typedefs.h"
#include "vector3.h"
#include "vector4.h"
#include "color_rgb.h"
#include "set.h"
#include "sun_light.h"
#include "mesh.h"
#include "camera.h"

namespace gfx{
class render_engine_parallel{
public:
    
    static constexpr utype invalid_crd = -1,_max_threads=16;
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
    
    //info
    const utype YRES,XRES,YXRES,T;
    //buffers
    vector4 *rgbz_buffer[_max_threads],*vertex_buffer=nullptr;
    utype _start[_max_threads],_end[_max_threads];
    uvector2 *vertex_screen_buffer=nullptr;
    utype vertex_buffer_size=0;
    
    render_engine_parallel(utype width,utype height);
    render_engine_parallel(utype width,utype height,utype vbuf);
    ~render_engine_parallel();
    
    //buffer handling
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
