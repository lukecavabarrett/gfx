#ifndef _INCLUDE_CAMERA_TRANSFORMATOR_H_
#define _INCLUDE_CAMERA_TRANSFORMATOR_H_

#include "gfx.h"

class camera_transformator : public transformator
{
public:
    static camera_transformator scale(dtype r);
    static camera_transformator translate(dtype mx,dtype my,dtype mz);
    static camera_transformator rotate_x(dtype theta);
    static camera_transformator rotate_y(dtype theta);
    static camera_transformator rotate_z(dtype theta);
    camera_transformator& push_back(const transformator& a);
    camera_transformator& push_front(const transformator& a);
};

#endif
