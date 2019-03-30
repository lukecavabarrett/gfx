#ifndef _INCLUDE_TRANSFORMATOR_H_
#define _INCLUDE_TRANSFORMATOR_H_

class vector3;

class transformator//4x4 matrix
{
    typedef floating_point_type T;
public:
    T value[4][4];
    typedef T value_type[4][4];
    typedef const value_type& const_value_type_reference;
    transformator();
    
    static transformator identity();
    static transformator scale(T r);
    static transformator translate(T mx,T my,T mz);
    static transformator rotate_x(T theta);
    static transformator rotate_y(T theta);
    static transformator rotate_z(T theta);
    transformator& push_back(const transformator& a);
    transformator& push_front(const transformator& b);
    vector3 apply(const vector3& p) const;
    void apply(vector3 *begin,vector3 *end) const;
    void apply(const vector3 *begin,const vector3 *end,vector3 *dst);
    std::string to_string();
};

#endif
