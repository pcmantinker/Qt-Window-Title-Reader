#include "win.h"

win::win()
{
}

QList<WindowInfo> win::getActiveWindows()
{
    QList<WindowInfo> windowTitles;
    HWND foregroundWindow = GetForegroundWindow();
    DWORD* processID = new DWORD;
    GetWindowText(foregroundWindow, buf, 255);
    GetWindowThreadProcessId(foregroundWindow, processID);
    DWORD p = *processID;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                  PROCESS_VM_READ,
                                  FALSE, p);
    TCHAR szProcessName[MAX_PATH];

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                                 &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }
    CloseHandle(hProcess);
    long pid = (long)p;
    QString windowTitle, processName;
#ifdef UNICODE
    windowTitle = QString::fromUtf16((ushort*)buf);
    processName = QString::fromUtf16((ushort*)szProcessName);
#else
    windowTitle = QString::fromLocal8Bit(buf);
    processName = QString::fromLocal8Bit(szProcessName);
#endif

    WindowInfo wi;
    wi.setPID(pid);
    wi.setWindowTitle(windowTitle);
    wi.setProcessName(processName);
    windowTitles.append(wi);
    return windowTitles;
}
