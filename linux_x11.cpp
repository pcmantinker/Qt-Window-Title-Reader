#include "linux_x11.h"

linux_x11::linux_x11()
{
}

Window * linux_x11::list (Display *disp, unsigned long *len) {
    Atom prop = XInternAtom(disp,"_NET_CLIENT_LIST",False), type;
    int form;
    unsigned long remain;
    unsigned char *list;
    int screen = DefaultScreen (disp);
    Window rootWindow = RootWindow (disp, screen);

    if (XGetWindowProperty(disp,rootWindow,prop,0,1024,False,XA_WINDOW,
                &type,&form,len,&remain,&list) != Success) {
        return 0;
    }

    return (Window*)list;
}

char *linux_x11::name (Display *disp, Window win) {
    Atom prop = XInternAtom(disp,"WM_NAME",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;


    if (XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,
                &type,&form,&len,&remain,&list) != Success) {

        return NULL;
    }

    return (char*)list;
}

char *linux_x11::command (Display *disp, Window win) {
    Atom prop = XInternAtom(disp,"WM_COMMAND",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;

    if (XGetWindowProperty(disp,win,prop,0,1024,False,XA_STRING,
                &type,&form,&len,&remain,&list) != Success) {

        return NULL;
    }

    return (char*)list;
}
