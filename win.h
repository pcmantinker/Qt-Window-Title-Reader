#ifndef WIN_H
#define WIN_H
#include <QtCore>
#include "qt_windows.h"

class win
{
public:
    win();
    void getWindowTitle();
    QString qstrmessage;

private:
    TCHAR buf[255];
};

#endif // WIN_H
