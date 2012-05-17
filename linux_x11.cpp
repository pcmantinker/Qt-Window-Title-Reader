#include "linux_x11.h"
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

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

QString linux_x11::processName(long pid)
{
    // construct command string
    QString command = "cat /proc/" + QString("%1").arg(pid) + "/status";
    // capture output in a FILE pointer returned from popen
    FILE * output = popen(command.toStdString().c_str(), "r");
    // initialize a buffer for storing the first line of the output
    char buffer[1024];
    // put the contents of the buffer into a QString
    QString line = QString::fromUtf8(fgets(buffer, sizeof(buffer), output));
    // close the process pipe
    pclose(output);
    // take right substring of line returned to get process name
    return line.right(line.length() - 6).replace("\n", "");
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
    if((int)len > 0)
    {
        for (int i=0;i<(int)len;i++) {
            n = name(disp,list[i]);
            c = command(disp, list[i]);
            cl = className(disp, list[i]);
            p = pid(disp, list[i]);
            long p_id = 0;
            QString pName;
            QString windowTitle;

            if(p!=NULL)
            {
                p_id = *p;
                pName = processName(p_id);
            }

            if(n!=NULL)
                windowTitle = QString::fromUtf8(n);

            WindowInfo wi;
            wi.setWindowTitle(windowTitle);
            wi.setProcessName(pName);
            wi.setPID(p_id);
            windowTitles.append(wi);
            delete n;
            delete c;
            delete cl;
            delete p;
        }
    }
    delete list;
    XCloseDisplay (disp);
    return windowTitles;
}
