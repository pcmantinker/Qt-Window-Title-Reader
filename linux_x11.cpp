#include "linux_x11.h"

linux_x11::linux_x11()
{
}

void linux_x11::enumerateWindows(Display *display, Window rootWindow)
{
//    Window parent;
//    Window *children;
//    Window *child;
//    quint32 nNumChildren;

//    XTextProperty wmName;
//    XTextProperty wmCommand;

//    int status = XGetWMName(display, rootWindow, &wmName);
//    if (status && wmName.value && wmName.nitems)
//    {
//        int i;
//        char **list;
//        status = XmbTextPropertyToTextList(display, &wmName, &list, &i);
//        if (status >= Success && i && *list)
//        {
//            qDebug() << "Found window with name:" << (char*) *list;
//        }

//        status = XGetCommand(display, rootWindow, &list, &i);
//        if (status >= Success && i && *list)
//        {
//            qDebug() << "... and Command:" << i << (char*) *list;
//        }

//        Window tf;
//        status = XGetTransientForHint(display, rootWindow, &tf);
//        if (status >= Success && tf)
//        {
//            qDebug() << "TF set!";
//        }

//        XWMHints *pHints = XGetWMHints(display, rootWindow);
//        if (pHints)
//        {
//            qDebug() << "Flags:" << pHints->flags
//                     << "Window group:" << pHints->window_group;
//        }
//    }

//    status = XQueryTree(display, rootWindow, &rootWindow, &parent, &children, &nNumChildren);
//    if (status == 0)
//    {
//        // Could not query window tree further, aborting
//        return;
//    }





//    Atom a = XInternAtom(display, "_NET_CLIENT_LIST" , true);
//    Atom actualType;
//    int format;
//    unsigned long numItems, bytesAfter;
//    unsigned char *data =0;
//    status = XGetWindowProperty(display,
//                                    rootWindow,
//                                    a,
//                                    0L,
//                                    (~0L),
//                                    false,
//                                    AnyPropertyType,
//                                    &actualType,
//                                    &format,
//                                    &numItems,
//                                    &bytesAfter,
//                                    &data);

//    if (status >= Success && numItems)
//    {
//        // success - we have data: Format should always be 32:
//        Q_ASSERT(format == 32);
//        // cast to proper format, and iterate through values:
//        quint32 *array = (quint32*) data;
//        for (quint32 k = 0; k < numItems; k++)
//        {
//            // get window Id:
//            Window w = (Window) array[k];
//            char* name = '\0';
//            status = XFetchName(display, w, &name);
//            if (status >= Success)
//            {
//                qDebug() << "Found: " << w << " " << name;
//            }
//            XFree(name);
//            qDebug() << "Scanned client window:" << w;
//        }
//        XFree(data);
//    }

//    if (nNumChildren == 0)
//    {
//        // No more children found. Aborting
//        return;
//    }

//    for (int i = 0; i < nNumChildren; i++)
//    {
//        enumerateWindows(display, children[i]);
//    }

//    XFree((char*) children);
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
