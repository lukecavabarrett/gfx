#include "transformator.h"

transformator::transformator() : value {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} {};

transformator transformator::identity() {
    transformator t;
    return t;
};

transformator transformator::scale() {
    transformator t;
    t.value[0][0]=t.value[1][1]=t.value[2][2]=t.value[3][3]=r;
    return t;
};


/*
class transformator//4x4 matrix
{
    typedef floating_point_type T;
public:
    T value[4][4];
    typedef T value_type[4][4];
    typedef const value_type& const_value_type_reference;
    //transformator(const_value_type_reference v) {value=v;}
    transformator() : value {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} {} //default identity
    
    //void scale(T r){ for(T& v:value)v*=r;}
    
    static transformator identity() {
        transformator t;
        return t;
    };
    static transformator scale(T r) {
        transformator t;
        t.value[0][0]=t.value[1][1]=t.value[2][2]=t.value[3][3]=r;
        return t;
    };
    static transformator translate(T mx,T my,T mz) {
        transformator t;
        t.value[0][3]=mx;
        t.value[1][3]=my;
        t.value[2][3]=mz;
        return t;
    };
    static transformator rotate_x(T theta) {
        transformator t;
        T c = std::cos(theta), s = std::sin(theta);
        t.value[1][1]=c;t.value[1][2]=s;
        t.value[2][1]=-s;t.value[2][2]=c;
        //t.value = {{1,0,0,0},{0,c,s,0},{0,-s,c,0},{0,0,0,1}};
        return t;
    };
    static transformator rotate_y(T theta) {
        transformator t;
        T c = std::cos(theta), s = std::sin(theta);
        t.value[0][0]=c;t.value[0][2]=-s;
        t.value[2][0]=s;t.value[2][2]=c;
        //t.value = {{c,0,-s,0},{0,1,0,0},{s,0,c,0},{0,0,0,1}};
        return t;
    };
    static transformator rotate_z(T theta) {
        transformator t;
        T c = std::cos(theta), s = std::sin(theta);
        t.value[0][0]=c;t.value[0][1]=s;
        t.value[1][0]=-s;t.value[1][1]=c;
        //t.value = {{c,s,0,0},{-s,c,0,0},{0,0,1,0},{0,0,0,1}};
        return t;
    };
    transformator& push_back(const transformator& a) {
        for(int j=0;j<4;j++){
            T b_0j = value[0][j], b_1j = value[1][j], b_2j = value[2][j], b_3j = value[3][j];
            value[0][j] = a.value[0][0] * b_0j + a.value[0][1] * b_1j + a.value[0][2] * b_2j + a.value[0][3] * b_3j;
            value[1][j] = a.value[1][0] * b_0j + a.value[1][1] * b_1j + a.value[1][2] * b_2j + a.value[1][3] * b_3j;
            value[2][j] = a.value[2][0] * b_0j + a.value[2][1] * b_1j + a.value[2][2] * b_2j + a.value[2][3] * b_3j;
            value[3][j] = a.value[3][0] * b_0j + a.value[3][1] * b_1j + a.value[3][2] * b_2j + a.value[3][3] * b_3j;
        }
        return *this;
    };
    transformator& push_front(const transformator& b) {
        for(int i=0;i<4;i++){
            T a_i0 = value[i][0], a_i1 = value[i][1], a_i2 = value[i][2], a_i3 = value[i][3];
            value[i][0] = a_i0 * b.value[0][0] + a_i1 * b.value[1][0] + a_i2 * b.value[2][0] + a_i3 * b.value[3][0];
            value[i][1] = a_i0 * b.value[0][1] + a_i1 * b.value[1][1] + a_i2 * b.value[2][1] + a_i3 * b.value[3][1];
            value[i][2] = a_i0 * b.value[0][2] + a_i1 * b.value[1][2] + a_i2 * b.value[2][2] + a_i3 * b.value[3][2];
            value[i][3] = a_i0 * b.value[0][3] + a_i1 * b.value[1][3] + a_i2 * b.value[2][3] + a_i3 * b.value[3][3];
        }
        return *this;
    };
    point apply(const point& p) {
        //T precision = value[3][0]*p.value[0] + value[3][1]*p.value[1] + value[3][2]*p.value[2] + value[3][3];
        //fprintf(stderr,"apply precision: %f\n",precision);
        return point(
            value[0][0]*p.value[0] + value[0][1]*p.value[1] + value[0][2]*p.value[2] + value[0][3],
            value[1][0]*p.value[0] + value[1][1]*p.value[1] + value[1][2]*p.value[2] + value[1][3],
            value[2][0]*p.value[0] + value[2][1]*p.value[1] + value[2][2]*p.value[2] + value[2][3]
        );
    };
    vector3<T> apply(const vector3<T>& p) {
        //T precision = value[3][0]*p.value[0] + value[3][1]*p.value[1] + value[3][2]*p.value[2] + value[3][3];
        //fprintf(stderr,"apply precision: %f\n",precision);
        return vector3<T>(
            value[0][0]*p.x + value[0][1]*p.y + value[0][2]*p.z + value[0][3],
            value[1][0]*p.x + value[1][1]*p.y + value[1][2]*p.z + value[1][3],
            value[2][0]*p.x + value[2][1]*p.y + value[2][2]*p.z + value[2][3]
        );
    };
    void apply(T begin[][3], T end[][3]) {
        T *b = (T *)begin, *e = (T *)end;
        for(;b!=e;b+=3){
            T b0 = b[0], b1 = b[1], b2 = b[2];
            b[0] = value[0][0]*b0 + value[0][1]*b1 + value[0][2]*b2 + value[0][3];
            b[1] = value[1][0]*b0 + value[1][1]*b1 + value[1][2]*b2 + value[1][3];
            b[2] = value[2][0]*b0 + value[2][1]*b1 + value[2][2]*b2 + value[2][3];
        }
    }
    void apply(T begin[][3], T end[][3], T dest[][3]) {
        T *b = (T *)begin, *e = (T *)end, *d = (T *)dest;
        for(;b!=e;b+=3,d+=3){
            T b0 = b[0], b1 = b[1], b2 = b[2];
            d[0] = value[0][0]*b0 + value[0][1]*b1 + value[0][2]*b2 + value[0][3];
            d[1] = value[1][0]*b0 + value[1][1]*b1 + value[1][2]*b2 + value[1][3];
            d[2] = value[2][0]*b0 + value[2][1]*b1 + value[2][2]*b2 + value[2][3];
        }
    }
    void apply(T *b, T *e, T *d) {
        for(;b!=e;b+=3,d+=3){
            T b0 = b[0], b1 = b[1], b2 = b[2];
            d[0] = value[0][0]*b0 + value[0][1]*b1 + value[0][2]*b2 + value[0][3];
            d[1] = value[1][0]*b0 + value[1][1]*b1 + value[1][2]*b2 + value[1][3];
            d[2] = value[2][0]*b0 + value[2][1]*b1 + value[2][2]*b2 + value[2][3];
        }
    }
    void apply(T *b, T *e) {
        for(;b!=e;b+=3){
            T b0 = b[0], b1 = b[1], b2 = b[2];
            b[0] = value[0][0]*b0 + value[0][1]*b1 + value[0][2]*b2 + value[0][3];
            b[1] = value[1][0]*b0 + value[1][1]*b1 + value[1][2]*b2 + value[1][3];
            b[2] = value[2][0]*b0 + value[2][1]*b1 + value[2][2]*b2 + value[2][3];
        }
    }
    std::string to_string() {
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
};*/
