#ifndef WINDOWINFO_H
#define WINDOWINFO_H
#include <QtCore>


class WindowInfo
{
public:
    WindowInfo();
    QString getWindowTitle();
    long getPID();
    QString getProcessName();

    void setWindowTitle(QString windowTitle);
    void setPID(long pid);
    void setProcessName(QString processName);

private:
    QString m_windowTitle;
    long m_pid;
    QString m_processName;
};

#endif // WINDOWINFO_H
