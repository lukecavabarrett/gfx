#include <bits/stdc++.h>
#include "gfx.h"

int main()
{

    gfx::set::set_pointer grid(new gfx::set("grid"));
    
    gfx::set::set_pointer row(new gfx::set("row"));

    gfx::set::mesh_pointer cube(new gfx::mesh(gfx::mesh::basic_shape::cube));

    row->meshes.emplace_back(gfx::transformator::translate(-2,0,0),cube);
    row->meshes.emplace_back(gfx::transformator::identity(),cube);
    row->meshes.emplace_back(gfx::transformator::translate(2,0,0),cube);
        
    grid->subsets.emplace_back(gfx::transformator::translate(0,-2,0),row);
    grid->subsets.emplace_back(gfx::transformator::identity(),row);
    grid->subsets.emplace_back(gfx::transformator::translate(0,2,0),row);
    
    grid->tree();
    
    gfx::render_engine re;
    gfx::transformator camera = gfx::transformator::identity().push_front(gfx::camera_transformator::rotate_x(M_PI/20)).push_front(gfx::camera_transformator::translate(0,-10,0));
    gfx::sun_light sun(0.3,0.7);
    gfx::color_rgb background(0.4);
    gfx::color_rgb ambient(0.4);
    
    gfx::render_engine::uvector2* h = new gfx::render_engine::uvector2 [rand()%10];
    
    //re.render(grid,nullptr,1024,768,camera,ambient,background,sun);
    
}
