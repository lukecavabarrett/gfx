#include <bits/stdc++.h>

//template<typename T>
typedef double T;

class point
{
public:
    typedef T value_type[3];
    value_type value;
    point() : value {0,0,0} {}
    point(T x,T y,T z) : value {x,y,z} {}
    std::string to_string(){
        std::string ret;
        ret+="[";
            for(int i=0;i<3;i++){
                ret+=" ";
                ret+=std::to_string(value[i]);
            }
            ret+=" ]";
        return ret;
    }
};


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

class color_rgb : public vector3<T>
{
public:
    using vector3<T>::vector3;
    using vector3<T>::operator=;
    static constexpr T inv_gamma = 1.0/2.2;
    static constexpr T g_a = 2.0;
    static constexpr T g_b = 1.3;
private:
    static int to_byte(T v)
    {
        return (int)(255 * std::max<T>(0, std::min<T>(1,v)));
    }
public:
    color_rgb (const vector3<T>& v)
    {
        vector3<T>::x=v.x;
        vector3<T>::y=v.y;
        vector3<T>::z=v.z;
    }
    operator vector3<T>()
    {
        return vector3<T>(vector3<T>::x,vector3<T>::y,vector3<T>::z);
    }
    int to_rgb() const
    {
        return to_byte(vector3<T>::x)<<16 | to_byte(vector3<T>::y)<<8 | to_byte(vector3<T>::z);
    }
    static color_rgb from_rgb(int w)
    {
        return color_rgb(((T)((w>>16)&0xff))/255.0,((T)((w>>8)&0xff))/255.0,((T)(w&0xff))/255.0);
    }
    int to_rgb_le() const
    {
        return to_byte(vector3<T>::z)<<16 | to_byte(vector3<T>::y)<<8 | to_byte(vector3<T>::x);
    }
    const vector3<T>& to_vec() const
    {
        return (const vector3<T>&)(*this);
    }
    color_rgb tonemap() const
    {
        vector3<T> powRGB = to_vec().power(g_b);
        return color_rgb((powRGB*((powRGB+std::pow(0.5/g_a,g_b)).inverse())).power(inv_gamma));
        //return (powRGB*((powRGB+std::pow(0.5/g_a,g_b)).inverse())).power(inv_gamma);
    }
    friend std::ostream& operator<<(std::ostream& os, const color_rgb& v)  
    {  
        os << '#' << std::setfill('0') << std::setw(6) << std::uppercase << std::hex << v.to_rgb();  
        return os;  
    }
};

class transformator//4x4 matrix
{
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
};

class object{
public:
    virtual int vertices_count() = 0;
    virtual int triangles_count() = 0;
    virtual void write_vertices_coord(T* dst) = 0;
    virtual void write_vertices_normals(T* dst) = 0;
    virtual void write_triangles_vertices(int* dst) = 0;
    virtual void write_triangles_colour(T* dst) = 0;
};

class gray_cube : public object {
    static void inline p_write(T*& dst,T x,T y,T z){*dst=x;++dst;*dst=y;++dst;*dst=z;++dst;};
    static void inline p_write(int*& dst,int x,int y,int z){*dst=x;++dst;*dst=y;++dst;*dst=z;++dst;};
public:
    int vertices_count() {return 24;}
    int triangles_count() {return 12;}
    void write_vertices_coord(T* dst) {
        //Z+
        p_write(dst,1,1,1);
        p_write(dst,-1,1,1);
        p_write(dst,-1,-1,1);
        p_write(dst,1,-1,1);
        //Z-
        p_write(dst,1,1,-1);
        p_write(dst,-1,1,-1);
        p_write(dst,-1,-1,-1);
        p_write(dst,1,-1,-1);
        //X+
        p_write(dst,1,1,1);
        p_write(dst,1,-1,1);
        p_write(dst,1,-1,-1);
        p_write(dst,1,1,-1);
        //X-
        p_write(dst,-1,1,1);
        p_write(dst,-1,-1,1);
        p_write(dst,-1,-1,-1);
        p_write(dst,-1,1,-1);
        //Y+
        p_write(dst,1,1,1);
        p_write(dst,-1,1,1);
        p_write(dst,-1,1,-1);
        p_write(dst,1,1,-1);
        //Y-
        p_write(dst,1,-1,1);
        p_write(dst,-1,-1,1);
        p_write(dst,-1,-1,-1);
        p_write(dst,1,-1,-1);
    }
    void write_vertices_normals(T* dst) {
        //Z+
        p_write(dst,0,0,1);
        p_write(dst,0,0,1);
        p_write(dst,0,0,1);
        p_write(dst,0,0,1);
        //Z-
        p_write(dst,0,0,-1);
        p_write(dst,0,0,-1);
        p_write(dst,0,0,-1);
        p_write(dst,0,0,-1);
        //X+
        p_write(dst,1,0,0);
        p_write(dst,1,0,0);
        p_write(dst,1,0,0);
        p_write(dst,1,0,0);
        //X-
        p_write(dst,-1,0,0);
        p_write(dst,-1,0,0);
        p_write(dst,-1,0,0);        
        p_write(dst,-1,0,0);
        //Y+
        p_write(dst,0,1,0);
        p_write(dst,0,1,0);
        p_write(dst,0,1,0);
        p_write(dst,0,1,0);
        //Y-
        p_write(dst,0,-1,0);
        p_write(dst,0,-1,0);
        p_write(dst,0,-1,0);
        p_write(dst,0,-1,0);
    }
    void write_triangles_vertices(int* dst) {
        //Z+
        p_write(dst,0,1,2);
        p_write(dst,2,3,0);
        //Z-
        p_write(dst,4,5,6);
        p_write(dst,6,7,4);
        //X+
        p_write(dst,8,9,10);
        p_write(dst,10,11,8);
        //X-
        p_write(dst,12,13,14);
        p_write(dst,14,15,12);
        //Y+
        p_write(dst,16,17,18);
        p_write(dst,18,19,16);
        //Y-
        p_write(dst,20,21,22);
        p_write(dst,22,23,20);
    }
    void write_triangles_colour(T* dst) {
        /*p_write(dst,0,0,1);
        p_write(dst,0,0,1);
        p_write(dst,0,0,1);
        p_write(dst,0,0,1);
        p_write(dst,0,1,0);
        p_write(dst,0,1,0);
        p_write(dst,0,1,0);
        p_write(dst,0,1,0);
        p_write(dst,1,0,0);
        p_write(dst,1,0,0);
        p_write(dst,1,0,0);
        p_write(dst,1,0,0);*/
        for(int i=0;i<12;i++)p_write(dst,0.2,0.2,0.2);
    }
};

class obj_handler : public object {
    static void inline p_write(T*& dst,T x,T y,T z){*dst=x;++dst;*dst=y;++dst;*dst=z;++dst;};
    static void inline p_write(int*& dst,int x,int y,int z){*dst=x;++dst;*dst=y;++dst;*dst=z;++dst;};
    int _vertices_count() {
        FILE *in = fopen(filename.c_str(),"r");
        int vc=0;
        char buffer[300];
        while(fgets(buffer,300,in))
        {
            if(buffer[0]=='v' && buffer[1]==' ')vc++;
        }
        fclose(in);
        fprintf(stderr,"%d vertices present in %s\n",vc,filename.c_str());
        return vc;
    }
    int _triangles_count() {
        FILE *in = fopen(filename.c_str(),"r");
        int tc=0;
        char buffer[300];
        while(fgets(buffer,300,in))
        {
            if(buffer[0]=='f' && buffer[1]==' ')tc++;
        }
        fclose(in);
        fprintf(stderr,"%d triangles present in %s\n",tc,filename.c_str());
        return tc;
    }
    std::string filename;
    int _vc,_tc;
    color_rgb color;
public:
    obj_handler(const std::string& s) : color(0.5){filename=s;_vc=_vertices_count();_tc=_triangles_count();}
    obj_handler(const char* s) : filename(s),color(0.5) {_vc=_vertices_count();_tc=_triangles_count();}
    void set_color(const color_rgb& c) {
        color=c;
    }
    int vertices_count() {
        return _vc;
    }
    int triangles_count() {
        return _tc;
    }
    void write_vertices_coord(T* dst) {
        FILE *in = fopen(filename.c_str(),"r");
        char buffer[300];
        int vc=0;
        while(fgets(buffer,300,in))
        {
            if(buffer[0]=='v' && buffer[1]==' ')
            {
                T x,y,z;
                sscanf(buffer,"%*s %lf %lf %lf",&x,&y,&z);
                ++vc;
                p_write(dst,x,y,z);
            }
        }
        fprintf(stderr,"%d vertices loaded from %s\n",vc,filename.c_str());
        fclose(in);
    }
    void write_vertices_normals(T* dst) {
        return write_vertices_coord(dst);
        FILE *in = fopen(filename.c_str(),"r");
        char buffer[300];
        int vnc=0;
        while(fgets(buffer,300,in))
        {
            if(buffer[0]=='v' && buffer[1]=='n')
            {
                ++vnc;
                T x,y,z;
                sscanf(buffer,"%*s %lf %lf %lf",&x,&y,&z);
                p_write(dst,x,y,z);
            }
        }
        fprintf(stderr,"%d vertices normals loaded from %s\n",vnc,filename.c_str());
        fclose(in);
    }
    void write_triangles_vertices(int* dst) {
        FILE *in = fopen(filename.c_str(),"r");
        char buffer[300];
        int tc=0;
        while(fgets(buffer,300,in))
        {
            if(buffer[0]=='f' && buffer[1]==' ')
            {
                ++tc;
                int x,y,z;
                sscanf(buffer,"%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",&x,&y,&z);
                if(x<0)x=_vc+x;else x--;
                if(y<0)y=_vc+y;else y--;
                if(z<0)z=_vc+z;else z--;
                p_write(dst,x,y,z);
            }
        }
        fprintf(stderr,"%d triangles loaded from %s\n",tc,filename.c_str());
        fclose(in);
    }
    void write_triangles_colour(T* dst) {
        for(int w=_tc;w--;)p_write(dst,color.x,color.y,color.z);
    }
};

/*

	private ColorRGB illuminate(Scene scene, SceneObject object, Vector3 P, Vector3 N, Vector3 O) {

		ColorRGB colourToReturn = new ColorRGB(0);

		ColorRGB I_a = scene.getAmbientLighting(); // Ambient illumination intensity

		ColorRGB C_diff = object.getColour(); // Diffuse colour defined by the object

		// Get Phong coefficients
		double k_d = object.getPhong_kD();
		double k_s = object.getPhong_kS();
		double alpha = object.getPhong_alpha();

		//Add ambient light term to start with
		ColorRGB ambient = C_diff.scale(I_a);
		colourToReturn = colourToReturn.add(ambient);

		// Loop over each point light source
		List<PointLight> pointLights = scene.getPointLights();
		for (int i = 0; i < pointLights.size(); i++){

			PointLight light = pointLights.get(i); // Select point light


			// Calculate point light constants
			double distanceToLight = light.getPosition().subtract(P).magnitude();
			ColorRGB C_spec = light.getColour();
			ColorRGB I = light.getIlluminationAt(distanceToLight);

			//Calculate L, V, R
			Vector3 L = light.getPosition().subtract(P).normalised();
			Vector3 V = O.subtract(P).normalised();
			Vector3 R = N.scale(L.dot(N)*2).subtract(L);

			Ray shadowRay = new Ray(P.add(L.scale(EPSILON)), L);

			double reachLights = 0;
			for (int k = 0; k<SHADOW_RAY_COUNT; k++) {
				PointLight lightSh = light;
				if(SHADOW_RAY_COUNT!=1)lightSh = new PointLight(light.getPosition().add(Vector3.randomInsideUnitSphere().scale(LIGHT_SIZE)), light.getColour(), light.getIntensity());
				Vector3 LSh = lightSh.getPosition().subtract(P).normalised();
				Ray shadowRaySh = new Ray(P.add(LSh.scale(EPSILON)), LSh);
				double distanceToLightSh = lightSh.getPosition().subtract(P).magnitude();
				reachLights+=scene.findIllumination(shadowRay, distanceToLightSh);
				//if(scene.findClosestIntersection(shadowRaySh).getDistance()>distanceToLightSh)reachLights++;
			}
			//Calculate ColorRGB diffuse and ColorRGB specular terms
			ColorRGB diffuse = C_diff.scale(I.scale(k_d*Math.max(0,N.dot(L)))).scale(reachLights/SHADOW_RAY_COUNT);
			ColorRGB specular = C_spec.scale(I.scale(k_s*Math.pow(Math.max(0,R.dot(V)),alpha))).scale(((double)reachLights)/SHADOW_RAY_COUNT);
			//Add these terms to colourToReturn
			colourToReturn = colourToReturn.add(diffuse);
			colourToReturn = colourToReturn.add(specular);
		}
		return colourToReturn ;
	}

*/

T *v,*v_end,*vn,*vn_end,*tc,*tc_end;
T *buf_1,*buf_2,*buf_1_end,*buf_2_end;
int *t,*t_end;
transformator camera;
color_rgb ambient_light, background_color;
vector3<T> sun_direction;
color_rgb sun_light;

#include <X11/Xlib.h> // must precede most other headers!
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cstdio>
#include <X11/Xutil.h>

constexpr int XRES=640,YRES=480;
constexpr T XREShalf=XRES/2,YREShalf=YRES/2;
int video_buffer [XRES*YRES];
T z_buffer[XRES*YRES];
Display *dsp;
Window win;
GC gc;
XImage *ximage;

constexpr T near_clip = 0.2, far_clip = 100000, multipl=100;

inline void put_pixel(T Px,T Py,T Pz,T Pr,T Pg,T Pb){
    int x=Px,y=Py;
    if(x>=0 && x<XRES && y>=0 && y<=YRES && Pz<z_buffer[y*XRES+x])
    {
        z_buffer[y*XRES+x]=Pz;
        video_buffer[y*XRES+x]=color_rgb(Pr,Pg,Pb).tonemap().to_rgb();
    }
}

void simple_px(int x,int y)
{
    if(x<0 || x>=XRES || y<0 || y>=YRES)return;
    video_buffer[y*XRES+x]=color_rgb(10.0,0,0).tonemap().to_rgb();
}

inline void flat_triangle(T Ax,T Ay,T Az,T Ar,T Ag,T Ab,T Bx,T By,T Bz,T Br,T Bg,T Bb,T Cx,T Cy,T Cz,T Cr,T Cg,T Cb){
    simple_px(Ax,Ay);
    simple_px(Bx,By);
    simple_px(Cx,Cy);
    fprintf(stderr,"(%d,%d) - (%d,%d) - (%d,%d) \n",(int)Ax,(int)Ay,(int)Bx,(int)By,(int)Cx,(int)Cy);
}

inline void gourad_triangle(T Ax,T Ay,T Az,T Ar,T Ag,T Ab,T Bx,T By,T Bz,T Br,T Bg,T Bb,T Cx,T Cy,T Cz,T Cr,T Cg,T Cb){
    //sort by y
    
    if(By<Ay)
    {
        T c;
        c=Ax;Ax=Bx;Bx=c;
        c=Ay;Ay=By;By=c;
        c=Az;Az=Bz;Bz=c;
        c=Ar;Ar=Br;Br=c;
        c=Ag;Ag=Bg;Bg=c;
        c=Ab;Ab=Bb;Bb=c;
    }
    if(Cy<By)
    {
        T c;
        c=Cx;Cx=Bx;Bx=c;
        c=Cy;Cy=By;By=c;
        c=Cz;Cz=Bz;Bz=c;
        c=Cr;Cr=Br;Br=c;
        c=Cg;Cg=Bg;Bg=c;
        c=Cb;Cb=Bb;Bb=c;
        if(By<Ay)
        {
            c=Ax;Ax=Bx;Bx=c;
            c=Ay;Ay=By;By=c;
            c=Az;Az=Bz;Bz=c;
            c=Ar;Ar=Br;Br=c;
            c=Ag;Ag=Bg;Bg=c;
            c=Ab;Ab=Bb;Bb=c;
        }
    }

    
    //fprintf(stderr,"(%d,%d) - (%d,%d) - (%d,%d) \n",(int)Ax,(int)Ay,(int)Bx,(int)By,(int)Cx,(int)Cy);
    //fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);
    
    T dx1,dr1,dg1,db1,dz1;
    
    if (By > Ay) {
		dx1=(Bx-Ax)/(By-Ay);
		dr1=(Br-Ar)/(By-Ay);
		dg1=(Bg-Ag)/(By-Ay);
		db1=(Bb-Ab)/(By-Ay);
        dz1=(Bz-Az)/(By-Ay);
	} else 
		 dx1=dr1=dg1=db1=dz1=0;

    T dx2,dr2,dg2,db2,dz2;
    
	if (Cy > Ay) {
		dx2=(Cx-Ax)/(Cy-Ay);
		dr2=(Cr-Ar)/(Cy-Ay);
		dg2=(Cg-Ag)/(Cy-Ay);
		db2=(Cb-Ab)/(Cy-Ay);
        dz2=(Cz-Az)/(Cy-Ay);
	} else 
		dx2=dr2=dg2=db2=dz2=0;

    T dx3,dr3,dg3,db3,dz3;
    
	if (Cy > By) {
		dx3=(Cx-Bx)/(Cy-By);
		dr3=(Cr-Br)/(Cy-By);
		dg3=(Cg-Bg)/(Cy-By);
		db3=(Cb-Bb)/(Cy-By);
        dz3=(Cz-Bz)/(Cy-By);
	} else 
		dx3=dr3=dg3=db3=dz3=0;

    T Sx=Ax,Sy=Ay,Sz=Az,Sr=Ar,Sg=Ag,Sb=Ab;
    T Ex=Ax,Ey=Ay,Ez=Az,Er=Ar,Eg=Ag,Eb=Ab;

	if(dx1 > dx2) {
		for(;Sy<=By;Sy++,Ey++) {
            T dr,dg,db,dz;
			if(Ex-Sx > 0) {
				dr=(Er-Sr)/(Ex-Sx);
				dg=(Eg-Sg)/(Ex-Sx);
				db=(Eb-Sb)/(Ex-Sx);
                dz=(Ez-Sz)/(Ex-Sx);
			} else 
				dr=dg=db=dz=0;
			T Px=Sx,Py=Sy,Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
			for(;Px < Ex;Px++) {
				put_pixel(Px,Py,Pz,Pr,Pg,Pb);
				Pr+=dr; Pg+=dg; Pb+=db; Pz+=dz;
			}
			Sx+=dx2; Sr+=dr2; Sg+=dg2; Sb+=db2; Sz+=dz2;
			Ex+=dx1; Er+=dr1; Eg+=dg1; Eb+=db1; Ez+=dz1;
		}

		Ex=Bx,Ey=By,Ez=Bz,Er=Br,Eg=Bg,Eb=Bb;
		for(;Sy<=Cy;Sy++,Ey++) {
            T dr,dg,db,dz;
			if(Ex-Sx > 0) {
				dr=(Er-Sr)/(Ex-Sx);
				dg=(Eg-Sg)/(Ex-Sx);
				db=(Eb-Sb)/(Ex-Sx);
                dz=(Ez-Sz)/(Ex-Sx);
			} else 
				dr=dg=db=0;
			T Px=Sx,Py=Sy,Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
			for(;Px < Ex;Px++) {
				put_pixel(Px,Py,Pz,Pr,Pg,Pb);
				Pr+=dr; Pg+=dg; Pb+=db; Pz+=dz;
			}
			Sx+=dx2; Sr+=dr2; Sg+=dg2; Sb+=db2; Sz+=dz2;
			Ex+=dx3; Er+=dr3; Eg+=dg3; Eb+=db3; Ez+=dz3;
		}
	} else {
		for(;Sy<=By;Sy++,Ey++) {
            T dr,dg,db,dz;
			if(Ex-Sx > 0) {
				dr=(Er-Sr)/(Ex-Sx);
				dg=(Eg-Sg)/(Ex-Sx);
				db=(Eb-Sb)/(Ex-Sx);
                dz=(Ez-Sz)/(Ex-Sx);
			} else 
				dr=dg=db=dz=0;
            T Px=Sx,Py=Sy,Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
			for(;Px < Ex;Px++) {
				put_pixel(Px,Py,Pz,Pr,Pg,Pb);
				Pr+=dr; Pg+=dg; Pb+=db; Pz+=dz;
			}
			Sx+=dx1; Sr+=dr1; Sg+=dg1; Sb+=db1; Sz+=dz1;
			Ex+=dx2; Er+=dr2; Eg+=dg2; Eb+=db2; Ez+=dz2;
		}

		Sx=Bx,Sy=By,Sz=Bz,Sr=Br,Sg=Bg,Sb=Bb;
		for(;Sy<=Cy;Sy++,Ey++) {
            T dr,dg,db,dz;
			if(Ex-Sx > 0) {
				dr=(Er-Sr)/(Ex-Sx);
				dg=(Eg-Sg)/(Ex-Sx);
				db=(Eb-Sb)/(Ex-Sx);
                dz=(Ez-Sz)/(Ex-Sx);
			} else 
				dr=dg=db=dz=0;

			T Px=Sx,Py=Sy,Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
			for(;Px < Ex;Px++) {
				put_pixel(Px,Py,Pz,Pr,Pg,Pb);
				Pr+=dr; Pg+=dg; Pb+=db; Pz+=dz;
			}
			Sx+=dx3; Sr+=dr3; Sg+=dg3; Sb+=db3; Sz+=dz3;
			Ex+=dx2; Er+=dr2; Eg+=dg2; Eb+=db2; Ez+=dz2;
		}
	}
}

inline void put_pixel_v2(int y,int x,T Pz,T Pr,T Pg,T Pb) {
    if(x>=0 && x<XRES && y>=0 && y<=YRES && Pz<z_buffer[y*XRES+x])
    {
        z_buffer[y*XRES+x]=Pz;
        video_buffer[y*XRES+x]=color_rgb(Pr,Pg,Pb).tonemap().to_rgb();
    }
}

inline void put_pixel_v3(int y,int x,T Pz,T Pr,T Pg,T Pb) {
    if(Pz<z_buffer[y*XRES+x])
    {
        z_buffer[y*XRES+x]=Pz;
        video_buffer[y*XRES+x]=color_rgb(Pr,Pg,Pb).tonemap().to_rgb();
    }
}

inline void gourad_triangle_v2(T Ax,T Ay,T Az,T Ar,T Ag,T Ab,T Bx,T By,T Bz,T Br,T Bg,T Bb,T Cx,T Cy,T Cz,T Cr,T Cg,T Cb){
    //sort by y
    
    if(By<Ay)
    {
        T c;
        c=Ax;Ax=Bx;Bx=c;
        c=Ay;Ay=By;By=c;
        c=Az;Az=Bz;Bz=c;
        c=Ar;Ar=Br;Br=c;
        c=Ag;Ag=Bg;Bg=c;
        c=Ab;Ab=Bb;Bb=c;
    }
    if(Cy<By)
    {
        T c;
        c=Cx;Cx=Bx;Bx=c;
        c=Cy;Cy=By;By=c;
        c=Cz;Cz=Bz;Bz=c;
        c=Cr;Cr=Br;Br=c;
        c=Cg;Cg=Bg;Bg=c;
        c=Cb;Cb=Bb;Bb=c;
        if(By<Ay)
        {
            c=Ax;Ax=Bx;Bx=c;
            c=Ay;Ay=By;By=c;
            c=Az;Az=Bz;Bz=c;
            c=Ar;Ar=Br;Br=c;
            c=Ag;Ag=Bg;Bg=c;
            c=Ab;Ab=Bb;Bb=c;
        }
    }

    
    //fprintf(stderr,"(%d,%d) - (%d,%d) - (%d,%d) \n",(int)Ax,(int)Ay,(int)Bx,(int)By,(int)Cx,(int)Cy);
    //fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);
    
    int iAy=(int)Ay,iBy=(int)By,iCy=(int)Cy;
    
    if(iAy==iBy && iBy==iCy)return;
    
    T dx1,dr1,dg1,db1,dz1;
    
    {
		dx1=(Bx-Ax)/(iBy-iAy);
		dr1=(Br-Ar)/(iBy-iAy);
		dg1=(Bg-Ag)/(iBy-iAy);
		db1=(Bb-Ab)/(iBy-iAy);
        dz1=(Bz-Az)/(iBy-iAy);
	} 

    T dx2,dr2,dg2,db2,dz2;
    
	{
		dx2=(Cx-Ax)/(iCy-iAy);
		dr2=(Cr-Ar)/(iCy-iAy);
		dg2=(Cg-Ag)/(iCy-iAy);
		db2=(Cb-Ab)/(iCy-iAy);
        dz2=(Cz-Az)/(iCy-iAy);
	}

    if(dx2<dx1){
        T c;
        c=Cx;Cx=Bx;Bx=c;
        c=Cy;Cy=By;By=c;
        c=Cz;Cz=Bz;Bz=c;
        c=Cr;Cr=Br;Br=c;
        c=Cg;Cg=Bg;Bg=c;
        c=Cb;Cb=Bb;Bb=c;
        c=dx1;dx1=dx2;dx2=c;
        c=dr1;dr1=dr2;dr2=c;
        c=dg1;dg1=dg2;dg2=c;
        c=db1;db1=db2;db2=c;
        c=dz1;dz1=dz2;dz2=c;
        
    }
    iBy=(int)By,iCy=(int)Cy;
    //now A is on top, B has d1<=d2 of C
    
    T dx3,dr3,dg3,db3,dz3;
    
    {
		dx3=(Cx-Bx)/(iCy-iBy);
		dr3=(Cr-Br)/(iCy-iBy);
		dg3=(Cg-Bg)/(iCy-iBy);
		db3=(Cb-Bb)/(iCy-iBy);
        dz3=(Cz-Bz)/(iCy-iBy);
	}

    T Sx=Ax,Sz=Az,Sr=Ar,Sg=Ag,Sb=Ab;
    T Ex=Ax,Ez=Az,Er=Ar,Eg=Ag,Eb=Ab;
    
    if(iBy<iCy){
        for(int y=iAy;y<=iBy;y++,Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1,Ex+=dx2,Ez+=dz2,Er+=dr2,Eg+=dg2,Eb+=db2){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
            //fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            //if(iEx>500){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);exit(0);}
            assert(iSx<=iEx+1);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v2(y,x,Pz,Pr,Pg,Pb);
            if(y==iBy)break;
        }
        Sx=Bx;Sz=Bz;Sr=Br;Sg=Bg;Sb=Bb;
        for(int y=iBy;y<=iCy;y++,Sx+=dx3,Sz+=dz3,Sr+=dr3,Sg+=dg3,Sb+=db3,Ex+=dx2,Ez+=dz2,Er+=dr2,Eg+=dg2,Eb+=db2){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
			//fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            //if(iEx<iSx){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) err %lf\n",Ax,Ay,Bx,By,Cx,Cy,Sx-Ex);exit(0);}
            assert(iSx<=iEx+1);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v2(y,x,Pz,Pr,Pg,Pb);
            if(y==iCy)break;
        }
    }else{
        for(int y=iAy;y<=iCy;y++,Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1,Ex+=dx2,Ez+=dz2,Er+=dr2,Eg+=dg2,Eb+=db2){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
            //fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            //if(iEx>500){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);exit(0);}
            assert(iSx<=iEx+1);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v2(y,x,Pz,Pr,Pg,Pb);
            if(y==iCy)break;
        }
        //Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1;
        Ex=Cx,Ez=Cz,Er=Cr,Eg=Cg,Eb=Cb;
        for(int y=iCy;y<=iBy;y++,Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1,Ex+=dx3,Ez+=dz3,Er+=dr3,Eg+=dg3,Eb+=db3){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
            //fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            //if(iEx<iSx){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) err %lf\n",Ax,Ay,Bx,By,Cx,Cy,Sx-Ex);exit(0);}
            assert(iSx<=iEx+1);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v2(y,x,Pz,Pr,Pg,Pb);
            if(y==iBy)break;
        }
    }
    
}

inline void gourad_triangle_v3(T Ax,T Ay,T Az,T Ar,T Ag,T Ab,T Bx,T By,T Bz,T Br,T Bg,T Bb,T Cx,T Cy,T Cz,T Cr,T Cg,T Cb){
    //sort by y
    
    if(By<Ay)
    {
        T c;
        c=Ax;Ax=Bx;Bx=c;
        c=Ay;Ay=By;By=c;
        c=Az;Az=Bz;Bz=c;
        c=Ar;Ar=Br;Br=c;
        c=Ag;Ag=Bg;Bg=c;
        c=Ab;Ab=Bb;Bb=c;
    }
    if(Cy<By)
    {
        T c;
        c=Cx;Cx=Bx;Bx=c;
        c=Cy;Cy=By;By=c;
        c=Cz;Cz=Bz;Bz=c;
        c=Cr;Cr=Br;Br=c;
        c=Cg;Cg=Bg;Bg=c;
        c=Cb;Cb=Bb;Bb=c;
        if(By<Ay)
        {
            c=Ax;Ax=Bx;Bx=c;
            c=Ay;Ay=By;By=c;
            c=Az;Az=Bz;Bz=c;
            c=Ar;Ar=Br;Br=c;
            c=Ag;Ag=Bg;Bg=c;
            c=Ab;Ab=Bb;Bb=c;
        }
    }

    
    //fprintf(stderr,"(%d,%d) - (%d,%d) - (%d,%d) \n",(int)Ax,(int)Ay,(int)Bx,(int)By,(int)Cx,(int)Cy);
    //fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);
    
    int iAy=(int)Ay,iBy=(int)By,iCy=(int)Cy;
    if(iAy>=YRES)return;
    if(iAy==iBy && iBy==iCy)return;
    
    T dx1,dr1,dg1,db1,dz1;
    
    {
		dx1=(Bx-Ax)/(iBy-iAy);
		dr1=(Br-Ar)/(iBy-iAy);
		dg1=(Bg-Ag)/(iBy-iAy);
		db1=(Bb-Ab)/(iBy-iAy);
        dz1=(Bz-Az)/(iBy-iAy);
	} 

    T dx2,dr2,dg2,db2,dz2;
    
	{
		dx2=(Cx-Ax)/(iCy-iAy);
		dr2=(Cr-Ar)/(iCy-iAy);
		dg2=(Cg-Ag)/(iCy-iAy);
		db2=(Cb-Ab)/(iCy-iAy);
        dz2=(Cz-Az)/(iCy-iAy);
	}

    if(dx2<dx1){
        T c;
        c=Cx;Cx=Bx;Bx=c;
        c=Cy;Cy=By;By=c;
        c=Cz;Cz=Bz;Bz=c;
        c=Cr;Cr=Br;Br=c;
        c=Cg;Cg=Bg;Bg=c;
        c=Cb;Cb=Bb;Bb=c;
        c=dx1;dx1=dx2;dx2=c;
        c=dr1;dr1=dr2;dr2=c;
        c=dg1;dg1=dg2;dg2=c;
        c=db1;db1=db2;db2=c;
        c=dz1;dz1=dz2;dz2=c;
        
    }
    iBy=(int)By,iCy=(int)Cy;
    //now A is on top, B has d1<=d2 of C
    
    T dx3,dr3,dg3,db3,dz3;
    
    {
		dx3=(Cx-Bx)/(iCy-iBy);
		dr3=(Cr-Br)/(iCy-iBy);
		dg3=(Cg-Bg)/(iCy-iBy);
		db3=(Cb-Bb)/(iCy-iBy);
        dz3=(Cz-Bz)/(iCy-iBy);
	}

    T Sx=Ax,Sz=Az,Sr=Ar,Sg=Ag,Sb=Ab;
    T Ex=Ax,Ez=Az,Er=Ar,Eg=Ag,Eb=Ab;
    
    if(iBy<iCy){
        if(iCy<0)return;
        if(iBy>0)
        {
            //y A->B
            //may want to jump if iAy<0
        int y=iAy,endBound= iBy < YRES ? iBy : YRES-1 ;
        if(iAy<0)
        {
            //simulate y iAy->0
            y=0;
            int miAy=-iAy;
            Sx+=dx1*miAy,Sz+=dz1*miAy,Sr+=dr1*miAy,Sg+=dg1*miAy,Sb+=db1*miAy,Ex+=dx2*miAy,Ez+=dz2*miAy,Er+=dr2*miAy,Eg+=dg2*miAy,Eb+=db2*miAy;
        }
        for(;/*y<=endBound  unnecessary since break*/;y++,Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1,Ex+=dx2,Ez+=dz2,Er+=dr2,Eg+=dg2,Eb+=db2){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
            //fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            //if(iEx>500){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);exit(0);}
            assert(iSx<=iEx);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            //bound x axis
            if(iSx<0)
            {
                iSx=-iSx;
                Pz+=dz*iSx,Pr+=dr*iSx,Pg+=dg*iSx,Pb+=db*iSx;
                iSx=0;
            }
            if(iEx>=XRES)iEx=XRES-1;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v3(y,x,Pz,Pr,Pg,Pb);
            if(y==endBound)break;
        }
        if(endBound==YRES-1)return;
        } else {
            //simulate y A->B
            Ex+=dx2*(iBy-iAy),Ez+=dz2*(iBy-iAy),Er+=dr2*(iBy-iAy),Eg+=dg2*(iBy-iAy),Eb+=db2*(iBy-iAy);
        }
        
        
        Sx=Bx;Sz=Bz;Sr=Br;Sg=Bg;Sb=Bb;
        int y=iBy,endBound= iCy < YRES ? iCy : YRES-1 ;
        if(iBy<0){
            //simulate y iBy -> 0
            y=0;
            int miBy=-iBy;
            Sx+=dx3*miBy,Sz+=dz3*miBy,Sr+=dr3*miBy,Sg+=dg3*miBy,Sb+=db3*miBy,Ex+=dx2*miBy,Ez+=dz2*miBy,Er+=dr2*miBy,Eg+=dg2*miBy,Eb+=db2*miBy;
        }
        
        for(;/*y<=endBound unnecessary because break*/;y++,Sx+=dx3,Sz+=dz3,Sr+=dr3,Sg+=dg3,Sb+=db3,Ex+=dx2,Ez+=dz2,Er+=dr2,Eg+=dg2,Eb+=db2){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
			//fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            //if(iEx>500){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);exit(0);}
            assert(iSx<=iEx);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            //bound x axis
            if(iSx<0)
            {
                iSx=-iSx;
                Pz+=dz*iSx,Pr+=dr*iSx,Pg+=dg*iSx,Pb+=db*iSx;
                iSx=0;
            }
            if(iEx>=XRES)iEx=XRES-1;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v3(y,x,Pz,Pr,Pg,Pb);
            if(y==endBound)break;
        }
    }else{
        
        //TODO fastener
        putc('*',stderr);
        for(int y=iAy;y<=iCy;y++,Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1,Ex+=dx2,Ez+=dz2,Er+=dr2,Eg+=dg2,Eb+=db2){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
            //fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            //if(iEx>500){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);exit(0);}
            assert(iSx<=iEx);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v2(y,x,Pz,Pr,Pg,Pb);
            if(y==iCy)break;
        }
        //Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1;
        Ex=Cx,Ez=Cz,Er=Cr,Eg=Cg,Eb=Cb;
        for(int y=iCy;y<=iBy;y++,Sx+=dx1,Sz+=dz1,Sr+=dr1,Sg+=dg1,Sb+=db1,Ex+=dx3,Ez+=dz3,Er+=dr3,Eg+=dg3,Eb+=db3){
            int iSx = (int)Sx, iEx = (int)Ex;
            T dr,dg,db,dz;
            //fprintf(stderr,"%d] [%d - %d] [%lf - %lf]\n",y,iSx,iEx,Sx,Ex);
            if(iEx<iSx){fprintf(stderr,"(%f,%f) - (%f,%f) - (%f,%f) \n",Ax,Ay,Bx,By,Cx,Cy);exit(0);}
            assert(iSx<=iEx);
            if(iEx>iSx){
				dr=(Er-Sr)/(iEx-iSx);
				dg=(Eg-Sg)/(iEx-iSx);
				db=(Eb-Sb)/(iEx-iSx);
                dz=(Ez-Sz)/(iEx-iSx);
			}
			T Pz=Sz,Pr=Sr,Pg=Sg,Pb=Sb;
            for(int x=iSx;x<=iEx;x++,Pz+=dz,Pr+=dr,Pg+=dg,Pb+=db)put_pixel_v2(y,x,Pz,Pr,Pg,Pb);
            if(y==iBy)break;
        }
    }
    
}

int render()
{
    //rand color
    //int c=0xff<<(8*(rand()%3));
    //std::fill(video_buffer,video_buffer+XRES*YRES,c);
    //put vertex illumination of buf_2 i.e. I_a + sum( I * k * max(dot(N,L),0) )
        vector3<T> sun_direction_render = sun_direction.normalised();//(camera.apply(sun_direction)-camera.apply(vector3<T>(0))).normalised();
        int i=0;
        for(T* x=buf_2,*vert=v,*vert_norm=vn;x!=buf_2_end;x+=3,vert+=3,vert_norm+=3,i++)
        {
            //ambient
            //x[0]=ambient_light.x;x[1]=ambient_light.y;x[2]=ambient_light.z;
            T nx=vert_norm[0]-vert[0],ny=vert_norm[1]-vert[1],nz=vert_norm[2]-vert[2];
            T magnitude = std::sqrt(nx*nx+ny*ny+nz*nz);nx/=magnitude;ny/=magnitude;nz/=magnitude;
            T dot = std::max<T>(0,sun_direction_render.x*nx + sun_direction_render.y*ny + sun_direction_render.z*nz);
            //fprintf(stderr,"vertex %i has dot lf\n",i,dot);
            x[0]=ambient_light.x + sun_light.x * dot;
            x[1]=ambient_light.y + sun_light.y * dot;
            x[2]=ambient_light.z + sun_light.z * dot;
        }
    //put vertex position on buf_1 TODO (x,y,prof) i.e. apply camera and perspective
        camera.apply(v,v_end,buf_1);
        for(T* x=buf_1;x!=buf_1_end;x+=3){
            if(x[2]<near_clip || x[2]>far_clip){
                x[0]=x[1]=-1;x[2]=0;//invalid
            } else {
                x[0]=x[0]*multipl/std::pow(x[2],0.5) + XREShalf;
                x[1]=x[1]*multipl/std::pow(x[2],0.5) + YREShalf;
                if(x[0]<0 || x[0]>XRES || x[1]<0 || x[1]>YRES){x[0]=x[1]=-1;x[2]=0;}
            }
        }
        //TODO FRUSTUM
    //do z-buffer algorithm TODO
    std::fill(video_buffer,video_buffer+XRES*YRES,background_color.tonemap().to_rgb());
    std::fill(z_buffer,z_buffer+XRES*YRES,std::numeric_limits<T>::infinity());
    color_rgb *col = (color_rgb *) tc;
    for(int *id_t=t;id_t!=t_end;id_t+=3,++col)if(buf_1[id_t[0]*3+2]!=0 && buf_1[id_t[1]*3+2]!=0 && buf_1[id_t[2]*3+2]!=0){
        gourad_triangle_v2(
            buf_1[id_t[0]*3],buf_1[id_t[0]*3+1],buf_1[id_t[0]*3+2],col->x*buf_2[id_t[0]*3],col->y*buf_2[id_t[0]*3+1],col->z*buf_2[id_t[0]*3+2],
            buf_1[id_t[1]*3],buf_1[id_t[1]*3+1],buf_1[id_t[1]*3+2],col->x*buf_2[id_t[1]*3],col->y*buf_2[id_t[1]*3+1],col->z*buf_2[id_t[1]*3+2],
            buf_1[id_t[2]*3],buf_1[id_t[2]*3+1],buf_1[id_t[2]*3+2],col->x*buf_2[id_t[2]*3],col->y*buf_2[id_t[2]*3+1],col->z*buf_2[id_t[2]*3+2]   
            );
    }
    //std::fill(video_buffer,video_buffer+XRES*YRES,0);
    //for(int x=0;x<XRES;x++)for(int y=0;y<YREShalf;y++)video_buffer[y*XRES+x]=0x00ffffff;
    return XPutImage(dsp, win,gc, ximage, 0, 0, 0, 0,XRES, YRES);
}

int run()
{
    dsp = XOpenDisplay( NULL );
    if(!dsp){ return 1; }

    int screen = DefaultScreen(dsp);
    unsigned int white = WhitePixel(dsp,screen);
    unsigned int black = BlackPixel(dsp,screen);

    win = XCreateSimpleWindow(dsp,
                            DefaultRootWindow(dsp),
                            0, 0,   // origin
                            XRES, YRES, // size
                            0, black, // border width/clr
                            white);   // backgrd clr

    Atom wmDelete=XInternAtom(dsp, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(dsp, win, &wmDelete, 1);

    gc = XCreateGC(dsp, win,
                    0,       // mask of values
                    NULL);   // array of values

    XSetForeground(dsp, gc, black);

    XEvent evt;
    long eventMask = StructureNotifyMask;
    eventMask |= ButtonPressMask|ButtonReleaseMask|KeyPressMask|KeyReleaseMask;
    XSelectInput(dsp, win, eventMask);
    
    Visual *visual = DefaultVisual(dsp, 0);
    ximage = XCreateImage(dsp, visual, 24,
                            ZPixmap, 0, (char *)video_buffer,
                            XRES, YRES, 32, 0);

    KeyCode keyQ;
    keyQ = XKeysymToKeycode(dsp, XStringToKeysym("Q"));

    XMapWindow(dsp, win);

    // wait until window appears
    do { XNextEvent(dsp,&evt); } while (evt.type != MapNotify);

    srand(time(0)); // only 1 sec resolution so use once per run
    //update_screen();
    render();
    int loop = 1;

    while (loop) {
    // for repeated fine seeding use:
    // struct timeval ti
    // gettimeofday(&ti,NULL);
    // srand((ti.tv_sec * 1000) + (ti.tv_usec / 1000));
    
    XNextEvent(dsp, &evt);

    switch (evt.type) {

        case (ButtonRelease) :

        printf("[%3d] ButtonRelease\n",evt.xkey.keycode);
        //update_screen();
        break;
        
        case (KeyPress) :

        //printf("[%3d] KeyPress\n",evt.xkey.keycode);
        //update_screen();
        break;

        case (KeyRelease) :

        printf("[%3d] KeyRelease\n",evt.xkey.keycode);
        if (evt.xkey.keycode == keyQ) loop = 0;
        if (evt.xkey.keycode == 38){
            //fprintf(stderr,"ROT_LEFT\n");
            camera.push_front(transformator::rotate_z(M_PI/30));
            render();
        }
        if (evt.xkey.keycode == 40){
            //fprintf(stderr,"ROT_RIGHT\n");
            camera.push_front(transformator::rotate_z(-M_PI/30));
            render();
        }
        if (evt.xkey.keycode == 52){
            //fprintf(stderr,"ROT_LEFT_CUBE\n");
            transformator::rotate_z(M_PI/30).apply(v,v_end);
            transformator::rotate_z(M_PI/30).apply(vn,vn_end);
            render();
        }
        if (evt.xkey.keycode == 54){
            //fprintf(stderr,"ROT_RIGHT_CUBE\n");
            transformator::rotate_z(-M_PI/30).apply(v,v_end);
            transformator::rotate_z(-M_PI/30).apply(vn,vn_end);
            render();
        }
        if (evt.xkey.keycode == 35){
            //fprintf(stderr,"SUN_UP\n");
            sun_direction.z+=1.0;
            std::cerr<<"sun_direction: "<<sun_direction<<std::endl;
            render();
        }
        if (evt.xkey.keycode == 61){
            //fprintf(stderr,"SUN_DOWN\n");
            sun_direction.z-=1.0;
            std::cerr<<"sun_direction: "<<sun_direction<<std::endl;
            render();
        }
        /*if (evt.xkey.keycode == 25){
            //fprintf(stderr,"GO_FORWARD\n");
            camera.push_back(transformator::translate(0,0,-0.3));
            render();
        }
        if (evt.xkey.keycode == 39){
            //fprintf(stderr,"GO_BACKWARDS\n");
            camera.push_back(transformator::translate(0,0,0.3));
            render();
        }
        if (evt.xkey.keycode == 27){
            //fprintf(stderr,"GO_FORWARD\n");
            camera.push_front(transformator::rotate_x(-M_PI/30));
            render();
        }
        if (evt.xkey.keycode == 41){
            //fprintf(stderr,"GO_BACKWARDS\n");
            camera.push_front(transformator::rotate_x(-M_PI/30));
            render();
        }*/
        //else render();
        break;

        case (ClientMessage) :

        if (evt.xclient.data.l[0] == wmDelete) loop = 0;
        break;

        default :

        break;
    }
    } 

    XDestroyWindow(dsp, win);
    XCloseDisplay(dsp);
    return 0;
}

void gourad_triangle_v2_tst(T ax,T ay,T bx,T by,T cx,T cy)
{
    return gourad_triangle_v2(ax,ay,0,0,0,0,bx,by,0,0,0,0,cx,cy,0,0,0,0);
}

int main()
{
    
    /*gourad_triangle_v2_tst(393.933009,325.688312,379.989929,339.637383,400.000000,341.490697);

    return 0;*/
    
    obj_handler my_cube("sphere.obj");
    my_cube.set_color(color_rgb(0.9,0.0,0.3));
    //gray_cube my_cube;
    background_color = color_rgb(0.8);
    ambient_light = color_rgb(0.2);
    sun_light = color_rgb(10);
    sun_direction = vector3<T>(-2,8,20);
    
    //std::cout<<sun_direction.dot(vector3<T>(0,0,1))<<std::endl;
    
    int nv = my_cube.vertices_count(), nvsize = nv*3;
    int nt = my_cube.triangles_count(), ntsize = nt*3;
    
    v = new T [nvsize]; v_end = v + nvsize;
    vn = new T [nvsize]; vn_end = vn + nvsize;
    my_cube.write_vertices_coord(v);
    my_cube.write_vertices_normals(vn);
    for(T *x=v,*y=vn;x!=v_end;x++,y++)*y+=*x;
    tc = new T [ntsize]; tc_end = tc + ntsize;
    t = new int [ntsize]; t_end = t + ntsize;
    my_cube.write_triangles_vertices(t);
    my_cube.write_triangles_colour(tc);
    buf_1 = new T [nvsize];buf_1_end=buf_1+nvsize;
    buf_2 = new T [nvsize];buf_2_end=buf_2+nvsize;
    
    camera.push_front(transformator::rotate_x(-M_PI/2));
    camera.push_front(transformator::translate(0,7,0));
    camera.push_front(transformator::rotate_x(-M_PI/4));
    
    /*printf("%d %d %d\n",t[0],t[1],t[2]);
    std::cout<<vector3<T>(v+3*t[0])<<std::endl;
    std::cout<<vector3<T>(v+3*t[1])<<std::endl;
    std::cout<<vector3<T>(v+3*t[2])<<std::endl;
    return 0;*/
    
    return run();
    
}
