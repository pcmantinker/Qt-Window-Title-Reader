#include "linux_x11.h"

linux_x11::linux_x11()
{
}

Window * linux_x11::list (Display *disp, unsigned long *len) {
    Atom prop = XInternAtom(disp,"_NET_CLIENT_LIST",False), type;
    int form;
    unsigned long remain;
    unsigned char *list;

    if (XGetWindowProperty(disp,XDefaultRootWindow(disp),prop,0,1024,False,XA_WINDOW,
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

    if (XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,
                           &type,&form,&len,&remain,&list) != Success) {

        return NULL;
    }

    return (char*)list;
}

char *linux_x11::className(Display *disp, Window win) {
    Atom prop = XInternAtom(disp,"WM_CLASS",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;

    if (XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,
                           &type,&form,&len,&remain,&list) != Success) {

        return NULL;
    }

    return (char*)list;
}

int* linux_x11::pid(Display *disp, Window win) {
    Atom prop = XInternAtom(disp,"_NET_WM_PID",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;

    if (XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,
                           &type,&form,&len,&remain,&list) != Success) {

        return NULL;
    }

    return (int*)list;
}

Window * linux_x11::active (Display *disp, unsigned long *len) {
    Atom prop = XInternAtom(disp,"_NET_ACTIVE_WINDOW",False), type;
    int form;
    unsigned long remain;
    unsigned char *list;

    if (XGetWindowProperty(disp,XDefaultRootWindow(disp),prop,0,1024,False,XA_WINDOW,
                           &type,&form,len,&remain,&list) != Success) {
        return 0;
    }

    return (Window*)list;
}

QList<WindowInfo> linux_x11::getActiveWindows()
{
    QList<WindowInfo> windowTitles;
    unsigned long len;
    Display *disp = XOpenDisplay(NULL);
    Window *list;
    char *n;
    char* c;
    char* cl;
    int* p;

    list = (Window*)active(disp,&len);
    for (int i=0;i<(int)len;i++) {
        n = name(disp,list[i]);
        c = command(disp, list[i]);
        cl = className(disp, list[i]);
        p = pid(disp, list[i]);
        qDebug() << i << " : " << n;
        QString windowTitle(n);
        QString processName(c);
        WindowInfo wi;
        wi.setWindowTitle(windowTitle);
        wi.setProcessName(processName);
        wi.setPID((long)*p);
        windowTitles.append(wi);
        delete n;
        delete c;
        delete cl;
        delete p;
    }
    delete list;
    XCloseDisplay (disp);
    return windowTitles;
}
