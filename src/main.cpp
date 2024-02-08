#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <iostream>

const int width = 800;
const int height = 600;

int xError(Display *display, XErrorEvent *event){
    char errorMessage[1024];
    XGetErrorText(display, event->error_code, errorMessage, sizeof(errorMessage));
    std::cerr << "X Error: "<<errorMessage << std::endl;
    return 0;
}

int main() {
    Display *display = XOpenDisplay(nullptr);
    if(!display){
        std::cerr<<"Failed to open X display"<<std::endl;
        return 1;
    }
    XSetErrorHandler((XErrorHandler)xError);

    static int visual_atribs[] = {
            GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_DRAWABLE_TYPE,
            GLX_WINDOW_BIT, GLX_DOUBLEBUFFER, true, None
    };

    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_atribs, &fbcount);
    if(!fbc){
        std::cerr<<"Failed retrieving a framebuffer config" <<std::endl;
        XCloseDisplay(display);
        return 1;
    }

    XVisualInfo* vi = glXGetVisualFromFBConfig(display, fbc[0]);
    Colormap cmap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);

    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;
    Window win = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, width, height,
                               0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XStoreName(display, win, "PicoForest");
    GLXContext ctx = glXCreateContext(display, vi, nullptr, GL_TRUE);
    glXMakeCurrent(display, win, ctx);
    XMapWindow(display, win);

    bool running = true;
    XEvent event;
    while(running){
        while(XPending(display) > 0) {
            XNextEvent(display, &event);
            switch (event.type){
                case KeyPress:
                    running = false;
                    break;
            }
        }
        glXSwapBuffers(display, win);
    }
    glXMakeCurrent(display, None, nullptr);
    glXDestroyContext(display, ctx);
    XDestroyWindow(display, win);
    XCloseDisplay(display);

    std::cout << "Hello, World!" << std::endl;


    return 0;
}
