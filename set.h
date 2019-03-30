#ifndef _INCLUDE_SET_H_
#define _INCLUDE_SET_H_

#include "typedefs.h"
#include "mesh.h"
#include "transformator.h"
#include <memory>
#include <functional>
#include <vector>

namespace gfx{
class set
{
    static utype _id_set_counter_;
public:
    typedef std::shared_ptr<mesh> mesh_pointer;
    typedef std::shared_ptr<set> set_pointer;
    typedef std::vector<std::pair<transformator,mesh_pointer>> mesh_vector;
    typedef std::vector<std::pair<transformator,set_pointer>> set_vector;
    //meshes
    mesh_vector meshes;
    //subsets
    set_vector subsets;
    //name
    const utype id;
    std::string name;
    
    void tree() const;
    
    set();
    set(const char *nm);
    set(const std::string& nm);
    ~set();
    
    utype count_sub_subsets() const ;
    utype count_sub_meshes() const ;
    utype count_sub_vertices() const ;
    utype count_sub_triangles() const ;
    utype max_sub_vertices() const ;
};
};
#endif
