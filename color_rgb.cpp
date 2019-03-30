#include "color_rgb.h"

color_rgb::color_rgb (const vector3<T>& v)
    {
        vector3<T>::x=v.x;
        vector3<T>::y=v.y;
        vector3<T>::z=v.z;
    }

operator color_rgb::vector3<T>()
    {
        return vector3<T>(vector3<T>::x,vector3<T>::y,vector3<T>::z);
    }

int color_rgb::to_rgb() const
    {
        return to_byte(vector3<T>::x)<<16 | to_byte(vector3<T>::y)<<8 | to_byte(vector3<T>::z);
    }

static color_rgb color_rgb::from_rgb(int w)
    {
        return color_rgb(((T)((w>>16)&0xff))/255.0,((T)((w>>8)&0xff))/255.0,((T)(w&0xff))/255.0U);
    }

int color_rgb::to_rgb_le() const
    {
        return to_byte(vector3<T>::z)<<16 | to_byte(vector3<T>::y)<<8 | to_byte(vector3<T>::x);
    }

const vector3<T>& color_rgb::to_vec() const
    {
        return (const vector3<T>&)(*this);
    }

color_rgb color_rgb::tonemap() const
    {
        vector3<T> powRGB = to_vec().power(g_b);
        return color_rgb((powRGB*((powRGB+std::pow(0.5/g_a,g_b)).inverse())).power(inv_gamma));
        //return (powRGB*((powRGB+std::pow(0.5/g_a,g_b)).inverse())).power(inv_gamma);
    }

std::ostream& operator<<(std::ostream& os, const color_rgb& v)
    {
        os << '#' << std::setfill('0') << std::setw(6) << std::uppercase << std::hex << v.to_rgb();
        return os;
    }

