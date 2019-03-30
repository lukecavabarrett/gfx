#ifndef _INCLUDE_VECTOR3_H_
#define _INCLUDE_VECTOR3_H_

class vector3
{
    typedef floating_point_type D;
public:
    D x,y,z;
    vector3();
    vector3(D v);
    vector3(D xp,D yp,D zp);
    vector3(D* p);
    D magnitude() const;
    
    vector3 operator+(const vector3& o) const ;
    void operator+=(const vector3& o);
    vector3 operator-(const vector3& o) const ;
    void operator-=(const vector3& o);
    vector3 operator*(const vector3& o) const ;
    void operator*=(const vector3& o);
    vector3 operator/(const vector3& o) const ;
    void operator/=(const vector3& o);
    vector3 operator+(D o) const ;
    void operator+=(D o){x+=o;y+=o;z+=o;}
    vector3 operator-(D o) const ;
    vector3 operator-() const ;
    void operator-=(D o);
    vector3 operator*(D o) const ;
    void operator*=(D o);
    vector3 operator/(D o) const ;
    void operator/=(D o);
    
    D distance(const vector3& o) const ;
    D distance_sqr(const vector3& o) const ;
    D dot(const vector3& o) const ;
    vector3 cross(const vector3& o) const ;
    vector3 power(D o) const ;
    vector3 inverse() const ;
    vector3 normalised() const ;
    void normalise();
    vector3 reflected_in(const vector3& n);
    static vector3 random_inside_unit_sphere();
    static D random_01();
    bool operator==(const vector3& o);
    bool operator!=(const vector3& o);
    friend std::ostream& operator<<(std::ostream& os, const vector3& v);
    vector3& operator=(const vector3& o);
};

#endif
