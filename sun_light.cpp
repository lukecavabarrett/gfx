#include "sun_light.h"
#include <deque>

namespace gfx{
    sun_light::sun_light() : vector(), color() {}
    sun_light::sun_light(dtype v,dtype c) : vector(v), color(c) {}
    sun_light::sun_light(const vector3& v,const color_rgb& c) : vector(v), color(c) {}
};
