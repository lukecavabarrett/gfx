#include <bits/stdc++.h>
#include "gfx.h"
#include <X11/Xlib.h> // must precede most other headers!
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cstdio>
#include <X11/Xutil.h>

int main()
{
    gfx::set::set_pointer scene(new gfx::set("scene"));

    gfx::set::mesh_pointer triangle(new gfx::mesh(gfx::mesh::basic_shape::triangle));

    gfx::set::mesh_pointer cube(new gfx::mesh(gfx::mesh::basic_shape::cube));

    scene->meshes.emplace_back(gfx::transformator::identity(),cube);
    
    scene->tree();

    gfx::render_engine re;
    gfx::camera camera(640,480);
    camera.rotate_x(M_PI/2).translate(0,-10,0).rotate_x(M_PI/20);
    
    gfx::sun_light sun(5,0.4);
    gfx::color_rgb background(0.1,0.1,0.2);
    gfx::color_rgb ambient(0.3);
    
    Display *dsp;
    Window win;
    GC gc;
    XImage *ximage;
    
    dsp = XOpenDisplay( NULL );
    if(!dsp){ return 1; }

    int screen = DefaultScreen(dsp);
    unsigned int white = WhitePixel(dsp,screen);
    unsigned int black = BlackPixel(dsp,screen);

    win = XCreateSimpleWindow(dsp,DefaultRootWindow(dsp),0, 0,640, 480,0, black,white);

    Atom wmDelete=XInternAtom(dsp, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(dsp, win, &wmDelete, 1);
    gc = XCreateGC(dsp, win,0,NULL);
    XSetForeground(dsp, gc, black);
    XEvent evt;
    long eventMask = StructureNotifyMask;
    eventMask |= ButtonPressMask|ButtonReleaseMask|KeyPressMask|KeyReleaseMask;
    XSelectInput(dsp, win, eventMask);
    
    Visual *visual = DefaultVisual(dsp, 0);
    ximage = XCreateImage(dsp, visual, 24,ZPixmap, 0, (char *)camera.video_buffer,640, 480, 32, 0);

    KeyCode keyQ;
    keyQ = XKeysymToKeycode(dsp, XStringToKeysym("Q"));

    XMapWindow(dsp, win);

    // wait until window appears
    do { XNextEvent(dsp,&evt); } while (evt.type != MapNotify);

    re.render(scene,camera,ambient,background,sun);
    XPutImage(dsp, win,gc, ximage, 0, 0, 0, 0,640, 480);
    int loop = 1;

    while (loop) {
    
    XNextEvent(dsp, &evt);

    switch (evt.type) {

        case (ButtonRelease) :

        //printf("[%3d] ButtonRelease\n",evt.xkey.keycode);
        //update_screen();
        break;
        
        case (KeyPress) :

        //printf("[%3d] KeyPress\n",evt.xkey.keycode);
        //update_screen();
        break;

        case (KeyRelease) :

        //printf("[%3d] KeyRelease\n",evt.xkey.keycode);
        if (evt.xkey.keycode == keyQ) loop = 0;
        if (evt.xkey.keycode == 38){
            //fprintf(stderr,"ROT_LEFT\n");
            camera.rotate_z(M_PI/30);
            re.render(scene,camera,ambient,background,sun);
            XPutImage(dsp, win,gc, ximage, 0, 0, 0, 0,640, 480);
        }
        if (evt.xkey.keycode == 40){
            //fprintf(stderr,"ROT_RIGHT\n");
            camera.rotate_z(-M_PI/30);
            re.render(scene,camera,ambient,background,sun);
            XPutImage(dsp, win,gc, ximage, 0, 0, 0, 0,640, 480);
        }
        /*
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
        */
        if (evt.xkey.keycode == 35){
            //fprintf(stderr,"SUN_UP\n");
            camera.translate(0,0,0.1);
            re.render(scene,camera,ambient,background,sun);
            XPutImage(dsp, win,gc, ximage, 0, 0, 0, 0,640, 480);
        }
        if (evt.xkey.keycode == 61){
            //fprintf(stderr,"SUN_DOWN\n");
            camera.translate(0,0,-0.1);
            re.render(scene,camera,ambient,background,sun);
            XPutImage(dsp, win,gc, ximage, 0, 0, 0, 0,640, 480);
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
