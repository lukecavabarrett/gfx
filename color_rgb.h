#ifndef COLOR_RGB_H
#define	COLOR_RGB_H
#include "gfx.h"

class color_rgb 
{

public:
    color_rgb (const vector3& v);
    operator vector3();
    int to_rgb() const;
    static color_rgb from_rgb(int w);
    int to_rgb_le() const; 
    const vector3& to_vec() const;
    color_rgb tonemap()i const;
    friend std::ostream& operator<<(std::ostream& os, const color_rgb& v);
};
#endif
