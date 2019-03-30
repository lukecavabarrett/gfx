#include <bits/stdc++.h>
#include "gfx.h"

int main()
{
    gfx::vector3 g = gfx::vector3::random_inside_unit_sphere();
    gfx::vector3 h = gfx::vector3::random_inside_unit_sphere().cross(g);
    std::cout<<h.dot(g)<<std::endl;
}
