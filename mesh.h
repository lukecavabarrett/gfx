#ifndef _INCLUDE_MESH_H_
#define _INCLUDE_MESH_H_

#include "typedefs.h"
#include "vector3.h"
#include "color_rgb.h"

namespace gfx{
class mesh
{
    static utype _id_mesh_counter_;
public:
    
    enum basic_shape {triangle,square,cube,sphere,tethraedron};//TODO implement just anything which is not the cube

    //vertices
    utype n_vertices;
        //locations
        vector3* v;
        //normals (location + normal format)
        vector3* vn;
        //colors
        color_rgb* vc;
    //triangles
    utype n_triangles;
        //indices
    struct utype3{
        utype i0,i1,i2;
        utype3() {}
        utype3(utype a,utype b,utype c) : i0(a), i1(b), i2(c) {}
    };
    utype3 *t;
    //name
    const utype id;
    std::string name;
        
    mesh();
    mesh(basic_shape s);
    mesh(const char* filename);//TODO
    ~mesh();
    
};
};


#endif
