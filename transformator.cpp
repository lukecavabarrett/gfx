#include "transformator.h"
#include <cstdlib>
#include <cmath>
namespace gfx{
transformator::transformator() : value {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} {};

transformator transformator::identity() {
    transformator t;
    return t;
};

transformator transformator::scale(dtype r) {
    transformator t;
    t.value[0][0]=t.value[1][1]=t.value[2][2]=t.value[3][3]=r;
    return t;
};

transformator transformator::translate(dtype mx,dtype my,dtype mz) {
    transformator t;
    t.value[0][3]=mx;
    t.value[1][3]=my;
    t.value[2][3]=mz;
    return t;
};

transformator transformator::rotate_x(dtype theta) {
    transformator t;
    dtype c = std::cos(theta), s = std::sin(theta);
    t.value[1][1]=c;t.value[1][2]=s;
    t.value[2][1]=-s;t.value[2][2]=c;
    //t.value = {{1,0,0,0},{0,c,s,0},{0,-s,c,0},{0,0,0,1}};
    return t;
};

transformator transformator::rotate_y(dtype theta) {
    transformator t;
    dtype c = std::cos(theta), s = std::sin(theta);
    t.value[0][0]=c;t.value[0][2]=-s;
    t.value[2][0]=s;t.value[2][2]=c;
    //t.value = {{c,0,-s,0},{0,1,0,0},{s,0,c,0},{0,0,0,1}};
    return t;
};

transformator transformator::rotate_z(dtype theta) {
    transformator t;
    dtype c = std::cos(theta), s = std::sin(theta);
    t.value[0][0]=c;t.value[0][1]=s;
    t.value[1][0]=-s;t.value[1][1]=c;
    //t.value = {{c,s,0,0},{-s,c,0,0},{0,0,1,0},{0,0,0,1}};
    return t;
};

transformator& transformator::push_back(const transformator& a) {
    for(int j=0;j<4;j++){
        dtype b_0j = value[0][j], b_1j = value[1][j], b_2j = value[2][j], b_3j = value[3][j];
        value[0][j] = a.value[0][0] * b_0j + a.value[0][1] * b_1j + a.value[0][2] * b_2j + a.value[0][3] * b_3j;
        value[1][j] = a.value[1][0] * b_0j + a.value[1][1] * b_1j + a.value[1][2] * b_2j + a.value[1][3] * b_3j;
        value[2][j] = a.value[2][0] * b_0j + a.value[2][1] * b_1j + a.value[2][2] * b_2j + a.value[2][3] * b_3j;
        value[3][j] = a.value[3][0] * b_0j + a.value[3][1] * b_1j + a.value[3][2] * b_2j + a.value[3][3] * b_3j;
    }
    return *this;
};

transformator& transformator::push_front(const transformator& b) {
    for(int i=0;i<4;i++){
        dtype a_i0 = value[i][0], a_i1 = value[i][1], a_i2 = value[i][2], a_i3 = value[i][3];
        value[i][0] = a_i0 * b.value[0][0] + a_i1 * b.value[1][0] + a_i2 * b.value[2][0] + a_i3 * b.value[3][0];
        value[i][1] = a_i0 * b.value[0][1] + a_i1 * b.value[1][1] + a_i2 * b.value[2][1] + a_i3 * b.value[3][1];
        value[i][2] = a_i0 * b.value[0][2] + a_i1 * b.value[1][2] + a_i2 * b.value[2][2] + a_i3 * b.value[3][2];
        value[i][3] = a_i0 * b.value[0][3] + a_i1 * b.value[1][3] + a_i2 * b.value[2][3] + a_i3 * b.value[3][3];
    }
    return *this;
};

vector3 transformator::apply(const vector3& p) const {
    //dtype precision = value[3][0]*p.value[0] + value[3][1]*p.value[1] + value[3][2]*p.value[2] + value[3][3];
    //fprintf(stderr,"apply precision: %f\n",precision);
    return vector3(
        value[0][0]*p.x + value[0][1]*p.y + value[0][2]*p.z + value[0][3],
        value[1][0]*p.x + value[1][1]*p.y + value[1][2]*p.z + value[1][3],
        value[2][0]*p.x + value[2][1]*p.y + value[2][2]*p.z + value[2][3]
    );
};

void transformator::apply(vector3 *begin,vector3 *end) const {
    for(;begin!=end;++begin){
        dtype b0 = begin->x, b1 = begin->y, b2 = begin->z;
        begin->x = value[0][0]*b0 + value[0][1]*b1 + value[0][2]*b2 + value[0][3];
        begin->y = value[1][0]*b0 + value[1][1]*b1 + value[1][2]*b2 + value[1][3];
        begin->z = value[2][0]*b0 + value[2][1]*b1 + value[2][2]*b2 + value[2][3];
    }
}

void transformator::apply(const vector3 *begin,const vector3 *end,vector3 *dst) const {
    for(;begin!=end;++begin,++dst){
        dtype b0 = begin->x, b1 = begin->y, b2 = begin->z;
        dst->x = value[0][0]*b0 + value[0][1]*b1 + value[0][2]*b2 + value[0][3];
        dst->y = value[1][0]*b0 + value[1][1]*b1 + value[1][2]*b2 + value[1][3];
        dst->z = value[2][0]*b0 + value[2][1]*b1 + value[2][2]*b2 + value[2][3];
    }
}

std::string transformator::to_string() {
    std::string ret;
    ret+= "[";
    for(int i=0;i<4;i++){
        ret+=" [";
        for(int j=0;j<4;j++){
            ret+=" ";
            ret+=std::to_string(value[i][j]);
        }
        ret+=" ]";
    }
    ret+=" ]";
    return ret;
}
};
