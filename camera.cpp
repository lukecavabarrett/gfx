#include "camera.h"
#include <cstdlib>
#include <cmath>
namespace gfx{
    
camera::camera() : forward(), inverse(), near(1), far(50000), h(0.64), w(0.48), video_buffer(nullptr) {}
camera::camera(const camera& o) : forward(o.forward), inverse(o.inverse), near(o.near), far(o.far), h(o.h), w(o.w) {}
camera::camera(utype xres, utype yres) : forward(), inverse(), near(1), far(50000), h(0.48*yres/xres), w(0.48), yres(yres), xres(xres), video_buffer(new int [yres*xres]) {}
camera::~camera(){if(video_buffer)delete[] video_buffer;}

camera& camera::scale(dtype r) {
    /*for(int i=0;i<4;i++)for(int j=0;j<4;j++)forward.value[i][j]*=r;
    r=1/r;
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)inverse.value[i][j]*=r;*/
    forward.push_back(transformator::scale(r));
    inverse.push_front(transformator::scale(1/r));
    return *this;
}

camera& camera::translate(dtype mx,dtype my,dtype mz) {
    /*for(int j=0;j<4;j++)forward.value[0][j]+=mx*forward.value[3][j];
    for(int j=0;j<4;j++)forward.value[1][j]+=my*forward.value[3][j];
    for(int j=0;j<4;j++)forward.value[2][j]+=mz*forward.value[3][j];*/
    forward.push_back(transformator::translate(mx,my,mz));
    inverse.push_front(transformator::translate(-mx,-my,-mz));
    return *this;
}
camera& camera::rotate_x(dtype theta){
    forward.push_back(transformator::rotate_x(theta));
    inverse.push_front(transformator::rotate_x(-theta));
    return *this;
}
camera& camera::rotate_y(dtype theta){
    forward.push_back(transformator::rotate_y(theta));
    inverse.push_front(transformator::rotate_y(-theta));
    return *this;
}
camera& camera::rotate_z(dtype theta){
    forward.push_back(transformator::rotate_y(theta));
    inverse.push_front(transformator::rotate_y(-theta));
    return *this;
}
    
};
