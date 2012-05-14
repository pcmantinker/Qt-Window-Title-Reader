#include "linux_x11.h"

linux_x11::linux_x11()
{
}

void linux_x11::enumerateWindows(Display *display, Window rootWindow)
{
    Window parent;
    Window *children;
    Window *child;
    quint32 nNumChildren;

    XTextProperty wmName;
    XTextProperty wmCommand;

    int status = XGetWMName(display, rootWindow, &wmName);
    if (status && wmName.value && wmName.nitems)
    {
        int i;
        char **list;
        status = XmbTextPropertyToTextList(display, &wmName, &list, &i);
        if (status >= Success && i && *list)
        {
            qDebug() << "Found window with name:" << (char*) *list;
        }

        status = XGetCommand(display, rootWindow, &list, &i);
        if (status >= Success && i && *list)
        {
            qDebug() << "... and Command:" << i << (char*) *list;
        }

        Window tf;
        status = XGetTransientForHint(display, rootWindow, &tf);
        if (status >= Success && tf)
        {
            qDebug() << "TF set!";
        }

        XWMHints *pHints = XGetWMHints(display, rootWindow);
        if (pHints)
        {
            qDebug() << "Flags:" << pHints->flags
                    << "Window group:" << pHints->window_group;
        }
    }

    status = XQueryTree(display, rootWindow, &rootWindow, &parent, &children, &nNumChildren);
    if (status == 0)
    {
        // Could not query window tree further, aborting
        return;
    }

    if (nNumChildren == 0)
    {
        // No more children found. Aborting
        return;
    }

    for (int i = 0; i < nNumChildren; i++)
    {
        enumerateWindows(display, children[i]);
    }

    XFree((char*) children);
}
