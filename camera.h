#ifndef _INCLUDE_CAMERA_H_
#define _INCLUDE_CAMERA_H_

#include "typedefs.h"
#include "vector3.h"
#include "transformator.h"
namespace gfx{
class camera
{
public:
    transformator forward,inverse;
    dtype near,far,h,w;
    utype yres=0,xres=0;
    int *video_buffer=nullptr;
    
    camera();
    camera(const camera& o);
    camera(utype xres, utype yres);
    ~camera();
    
    camera& scale(dtype r);
    camera& translate(dtype mx,dtype my,dtype mz);
    camera& rotate_x(dtype theta);
    camera& rotate_y(dtype theta);
    camera& rotate_z(dtype theta);
    
    //friend std::ostream& operator<<(std::ostream& os, const transformator& v);
    transformator& operator=(const transformator& o);
    std::string to_string() const;
};
}
#endif
