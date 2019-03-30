#ifndef _INCLUDE_SUN_LIGHT_H_
#define _INCLUDE_SUN_LIGHT_H_

#include "typedefs.h"
#include "vector3.h"
#include "color_rgb.h"

namespace gfx{
class sun_light
{
public:
    vector3 vector;//vector pointing the sun from the origin in the scene representation
    color_rgb color;//light color
    
    sun_light();
    sun_light(dtype v,dtype c);
    sun_light(const vector3& v,const color_rgb& c);
};
}
#endif
