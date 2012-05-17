/*
  Linux/X11 specific code for obtaining information about the frontmost window
*/

#ifndef LINUX_X11_H
#define LINUX_X11_H

#include <QtCore>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include "windowinfo.h"

class linux_x11
{
public:
    linux_x11();
    QList<WindowInfo> getActiveWindows();

private:
    Window* active(Display *disp, unsigned long *len);
    char *name (Display *disp, Window win);
    int *pid(Display *disp, Window win);
    QString processName(long pid);
};

#endif // LINUX_X11_H
