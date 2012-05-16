#ifndef WIN_H
#define WIN_H
#include <QtCore>
#include "qt_windows.h"
#include "psapi.h"
#include "windowinfo.h"

class win : public QObject
{
    Q_OBJECT

public:
    win();
    QList<WindowInfo> getActiveWindows();

private:
    TCHAR buf[255];
};

#endif // WIN_H
