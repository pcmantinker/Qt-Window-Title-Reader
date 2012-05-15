#ifndef LINUX_X11_H
#define LINUX_X11_H

#include <QtCore>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

class linux_x11
{
public:
    linux_x11();
    Window* list(Display *disp, unsigned long *len);
    Window* active(Display *disp, unsigned long *len);
    char *name (Display *disp, Window win);
    char *command(Display *disp, Window win);
    void getWindowTitle();
};

#endif // LINUX_X11_H
