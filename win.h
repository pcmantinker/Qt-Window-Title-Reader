#ifndef WIN_H
#define WIN_H
#include <QtCore>
#ifdef Q_WS_WIN
#include "qt_windows.h"
#endif

class win
{
public:
    win();
    void getWindowTitle();
    QString qstrmessage;

private:
    #ifdef Q_WS_WIN
    TCHAR buf[255];
    #endif
};

#endif // WIN_H
