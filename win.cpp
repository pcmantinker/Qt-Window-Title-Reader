#include "win.h"

win::win()
{
}

void win::getWindowTitle()
{
    #ifdef Q_WS_WIN
    GetWindowText(GetForegroundWindow(), buf, 255);
#ifdef UNICODE
    qstrmessage = QString::fromUtf16((ushort*)buf);
#else
    qstrmessage = QString::fromLocal8Bit(buf);
#endif
    qDebug() << qstrmessage;
#endif
}
