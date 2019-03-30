#include "camera_transformator.h"
#include <cstdlib>
#include <cmath>
namespace gfx{
camera_transformator camera_transformator::scale(dtype r) {
        camera_transformator t;
        t.value[0][0]=t.value[1][1]=t.value[2][2]=t.value[3][3]=1/r;
        return t;
};

camera_transformator camera_transformator::translate(dtype mx,dtype my,dtype mz) {
    camera_transformator t;
    t.value[0][3]=-mx;
    t.value[1][3]=-my;
    t.value[2][3]=-mz;
    return t;
};

camera_transformator camera_transformator::rotate_x(dtype theta) {
    camera_transformator t;
    dtype c = std::cos(-theta), s = std::sin(-theta);
    t.value[1][1]=c;t.value[1][2]=s;
    t.value[2][1]=-s;t.value[2][2]=c;
    //t.value = {{1,0,0,0},{0,c,s,0},{0,-s,c,0},{0,0,0,1}};
    return t;
};

camera_transformator camera_transformator::rotate_y(dtype theta) {
    camera_transformator t;
    dtype c = std::cos(-theta), s = std::sin(-theta);
    t.value[0][0]=c;t.value[0][2]=-s;
    t.value[2][0]=s;t.value[2][2]=c;
    //t.value = {{c,0,-s,0},{0,1,0,0},{s,0,c,0},{0,0,0,1}};
    return t;
};

camera_transformator camera_transformator::rotate_z(dtype theta) {
    camera_transformator t;
    dtype c = std::cos(-theta), s = std::sin(-theta);
    t.value[0][0]=c;t.value[0][1]=s;
    t.value[1][0]=-s;t.value[1][1]=c;
    //t.value = {{c,s,0,0},{-s,c,0,0},{0,0,1,0},{0,0,0,1}};
    return t;
};

camera_transformator& camera_transformator::push_back(const transformator& b) {
    for(int i=0;i<4;i++){
        dtype a_i0 = value[i][0], a_i1 = value[i][1], a_i2 = value[i][2], a_i3 = value[i][3];
        value[i][0] = a_i0 * b.value[0][0] + a_i1 * b.value[1][0] + a_i2 * b.value[2][0] + a_i3 * b.value[3][0];
        value[i][1] = a_i0 * b.value[0][1] + a_i1 * b.value[1][1] + a_i2 * b.value[2][1] + a_i3 * b.value[3][1];
        value[i][2] = a_i0 * b.value[0][2] + a_i1 * b.value[1][2] + a_i2 * b.value[2][2] + a_i3 * b.value[3][2];
        value[i][3] = a_i0 * b.value[0][3] + a_i1 * b.value[1][3] + a_i2 * b.value[2][3] + a_i3 * b.value[3][3];
    }
    return *this;
};

camera_transformator& camera_transformator::push_front(const transformator& a) {
    for(int j=0;j<4;j++){
        dtype b_0j = value[0][j], b_1j = value[1][j], b_2j = value[2][j], b_3j = value[3][j];
        value[0][j] = a.value[0][0] * b_0j + a.value[0][1] * b_1j + a.value[0][2] * b_2j + a.value[0][3] * b_3j;
        value[1][j] = a.value[1][0] * b_0j + a.value[1][1] * b_1j + a.value[1][2] * b_2j + a.value[1][3] * b_3j;
        value[2][j] = a.value[2][0] * b_0j + a.value[2][1] * b_1j + a.value[2][2] * b_2j + a.value[2][3] * b_3j;
        value[3][j] = a.value[3][0] * b_0j + a.value[3][1] * b_1j + a.value[3][2] * b_2j + a.value[3][3] * b_3j;
    }
    return *this;
};
};
