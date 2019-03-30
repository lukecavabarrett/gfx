#include <bits/stdc++.h>
#include "gfx.h"

int main()
{
    gfx::set::mesh_pointer cube(new gfx::mesh(gfx::mesh::basic_shape::cube));
    
    gfx::set::set_pointer row(new gfx::set("row"));
    
    row->meshes.emplace_back(gfx::transformator::translate(-1,0,0),cube);
    row->meshes.emplace_back(gfx::transformator::identity(),cube);
    row->meshes.emplace_back(gfx::transformator::translate(1,0,0),cube);
    
    gfx::set::set_pointer grid(new gfx::set("grid"));
    
    grid->subsets.emplace_back(gfx::transformator::translate(0,-1,0),row);
    grid->subsets.emplace_back(gfx::transformator::identity(),row);
    grid->subsets.emplace_back(gfx::transformator::translate(0,1,0),row);
    
    grid->tree();
    
    std::cout<<grid->max_sub_vertices()<<std::endl;
}
