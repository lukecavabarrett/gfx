template<typename D> class vector3
{
public:
    D x,y,z;
    vector3(){x=y=z=0;};
    vector3(D v){x=y=z=v;}
    vector3(D xp,D yp,D zp){x=xp;y=yp;z=zp;};
    vector3(D* p){x=*p;y=p[1];z=p[2];}
    D magnitude() const {return std::sqrt(x*x+y*y+z*z);};
    
    vector3 operator+(const vector3& o) const {return vector3(x+o.x,y+o.y,z+o.z);}
    void operator+=(const vector3& o){x+=o.x;y+=o.y;z+=o.z;}
    vector3 operator-(const vector3& o) const {return vector3(x-o.x,y-o.y,z-o.z);}
    void operator-=(const vector3& o){x-=o.x;y-=o.y;z-=o.z;}
    vector3 operator*(const vector3& o) const {return vector3(x*o.x,y*o.y,z*o.z);}
    void operator*=(const vector3& o){x*=o.x;y*=o.y;z*=o.z;}
    vector3 operator/(const vector3& o) const {return vector3(x/o.x,y/o.y,z/o.z);}
    void operator/=(const vector3& o){x/=o.x;y/=o.y;z/=o.z;}
    vector3 operator+(D o) const {return vector3(x+o,y+o,z+o);}
    void operator+=(D o){x+=o;y+=o;z+=o;}
    vector3 operator-(D o) const {return vector3(x-o,y-o,z-o);}
    vector3 operator-() const {return vector3(-x,-y,-z);}
    void operator-=(D o){x-=o;y-=o;z-=o;}
    vector3 operator*(D o) const {return vector3(x*o,y*o,z*o);}
    void operator*=(D o){x*=o;y*=o;z*=o;}
    vector3 operator/(D o) const {return vector3(x/o,y/o,z/o);}
    void operator/=(D o){x/=o;y/=o;z/=o;}
    
    D distance(const vector3& o) const {return std::sqrt((x-o.x)*(x-o.x)+(y-o.y)*(y-o.y)+(z-o.z)*(z-o.z));}
    D distance_sqr(const vector3& o) const {return (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y)+(z-o.z)*(z-o.z);}
    D dot(const vector3& o) const {return x*o.x+y*o.y+z*o.z;}
    vector3 cross(const vector3& o) const {return vector3(y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x);}
    vector3 power(D o) const {return vector3(std::pow(x,o),std::pow(y,o),std::pow(z,o));}
    vector3 inverse() const {return vector3(1/x,1/y,1/z);}
    vector3 normalised() const {D m=magnitude();return vector3(x/m,y/m,z/m);}
    void normalise(){D m=magnitude();x/=m;y/=m;z/=m;}
    vector3 reflected_in(const vector3& n) const
    {
        D d = dot(n)*2;
        return vector3(d*n.x-x,d*n.y-y,d*n.z-z);
    }
    static vector3 random_inside_unit_sphere()
    {
        D r = ((D) std::rand() / (RAND_MAX));
        D theta = ((D) std::rand() / (RAND_MAX)) * M_PIl;
        D phi = ((D) std::rand() / (RAND_MAX)) * M_PIl * 2;
        return vector3(r*std::sin(theta)*std::cos(phi),
                       r*std::sin(theta)*std::sin(phi),
                       r*std::cos(theta));
    }
    static D random_01()
    {
        return ((D) std::rand() / (RAND_MAX));
    }
    bool operator==(const vector3& o) const {return x==o.x && y==o.y && z==o.z;}
    friend std::ostream& operator<<(std::ostream& os, const vector3& v)  
    {  
        os << '[' << v.x << ',' << v.y << ',' << v.z << ']';  
        return os;  
    }
    vector3& operator=(const vector3& o)
    {
        x=o.x;y=o.y;z=o.z;
        return *this;
    }
};
