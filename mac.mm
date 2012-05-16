#include "mac.h"
#include "Cocoa/Cocoa.h"

QList<WindowInfo> Mac::getActiveWindows()
{
    QList<WindowInfo> windowTitles;

    // get frontmost process for currently active application
    ProcessSerialNumber psn = { 0L, 0L };
    OSStatus err = GetFrontProcess(&psn);

    CFStringRef processName = NULL;
    err = CopyProcessName(&psn, &processName);

    NSString *pname = (NSString *)processName;

    // loop through all application windows
    int i = 0;
    CFArrayRef windowList = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements, kCGNullWindowID);
    for (NSMutableDictionary* entry in (NSArray*)windowList)
    {
        NSString* ownerName = [entry objectForKey:(id)kCGWindowOwnerName];
        NSString *name = [entry objectForKey:@"kCGWindowName" ];
        NSInteger ownerPID = [[entry objectForKey:(id)kCGWindowOwnerPID] integerValue];
        NSInteger layer = [[entry objectForKey:@"kCGWindowLayer"] integerValue];
        if(layer == 0)
        {
            if([ownerName isEqualToString:pname])
            {
                NSRange range;
                range.location = 0;
                range.length = [ownerName length];

                unichar *chars = new unichar[range.length];
                [ownerName getCharacters:chars range:range];
                QString owner = QString::fromUtf16(chars, range.length);

                range.length = [name length];

                chars = new unichar[range.length];
                [name getCharacters:chars range:range];
                QString windowTitle = QString::fromUtf16(chars, range.length);
                delete[] chars;

                long pid = (long)ownerPID;

                WindowInfo wi;
                wi.setProcessName(owner);
                wi.setWindowTitle(windowTitle);
                wi.setPID(pid);
                windowTitles.append(wi);
            }
            i++;
        }
    }
    CFRelease(windowList);
    CFRelease(processName);

    return windowTitles;
}

