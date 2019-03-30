#ifndef _INCLUDE_VECTOR4_H_
#define _INCLUDE_VECTOR4_H_

#include "typedefs.h"
#include <iostream>
namespace gfx{
class vector4
{
    
public:
    dtype x,y,z,w;
    vector4();
    vector4(dtype v);
    vector4(dtype xp,dtype yp,dtype zp,dtype wp);
    vector4(const vector4& o);
    vector4(const vector4& o,dtype wp);
    dtype magnitude() const;
    
    vector4 operator+(const vector4& o) const ;
    void operator+=(const vector4& o);
    vector4 operator-(const vector4& o) const ;
    void operator-=(const vector4& o);
    vector4 operator*(const vector4& o) const ;
    void operator*=(const vector4& o);
    vector4 operator/(const vector4& o) const ;
    void operator/=(const vector4& o);
    vector4 operator+(dtype o) const ;
    void operator+=(dtype o);
    vector4 operator-(dtype o) const ;
    vector4 operator-() const ;
    void operator-=(dtype o);
    vector4 operator*(dtype o) const ;
    void operator*=(dtype o);
    vector4 operator/(dtype o) const ;
    void operator/=(dtype o);
    
    dtype distance(const vector4& o) const ;
    dtype distance_sqr(const vector4& o) const ;
    dtype dot(const vector4& o) const ;
    vector4 power(dtype o) const ;
    vector4 inverse() const ;
    vector4 normalised() const ;
    void normalise();
    vector4 reflected_in(const vector4& n) const;
    static dtype random_01();
    bool operator==(const vector4& o) const;
    bool operator!=(const vector4& o) const;
    friend std::ostream& operator<<(std::ostream& os, const vector4& v);
    vector4& operator=(const vector4& o);
};
}
#endif
