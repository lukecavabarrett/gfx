#ifndef _INCLUDE_TRANSFORMATOR_H_
#define _INCLUDE_TRANSFORMATOR_H_

#include "typedefs.h"
#include "vector3.h"
namespace gfx{
class transformator
{
public:
    dtype value[4][4];
    typedef dtype value_type[4][4];
    typedef const value_type& const_value_type_reference;
    transformator();
    
    static transformator identity();
    static transformator scale(dtype r);
    static transformator translate(dtype mx,dtype my,dtype mz);
    static transformator rotate_x(dtype theta);
    static transformator rotate_y(dtype theta);
    static transformator rotate_z(dtype theta);
    transformator& push_back(const transformator& a);
    transformator& push_front(const transformator& b);
    vector3 apply(const vector3& p) const;
    void apply(vector3 *begin,vector3 *end) const;
    void apply(const vector3 *begin,const vector3 *end,vector3 *dst) const;
    friend std::ostream& operator<<(std::ostream& os, const transformator& v);
    transformator& operator=(const transformator& o);
    std::string to_string() const;
};
}
#endif
