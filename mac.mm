#include "mac.h"
#include "Cocoa/Cocoa.h"

void Mac::getWindowTitle()
{
    // get front process for currently active application
    ProcessSerialNumber psn = { 0L, 0L };
    OSStatus err = GetFrontProcess(&psn);

    CFStringRef processName = NULL;
    err = CopyProcessName(&psn, &processName);
    CFIndex length = CFStringGetLength(processName);

    QString string(length, Qt::Uninitialized);
    CFStringGetCharacters(processName, CFRangeMake(0, length), reinterpret_cast<UniChar *>
                          (const_cast<QChar *>(string.unicode())));
    qDebug() << string;
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
            //if([ownerName isEqualToString:@"Firefox"] || [ownerName isEqualToString:@"Google Chrome"] || [ownerName isEqualToString:@"Safari"] )
            if([ownerName isEqualToString:pname])
                    NSLog(@"%@:%d name: %@, layer: %d, i: %d", ownerName, ownerPID, name, layer, i);
                i++;
        }
    }
    CFRelease(windowList);
    CFRelease(processName);
//            NSRange range;
//            range.location = 0;
//            range.length = [title length];
////            QString result(range.length, QChar(0));

//            unichar *chars = new unichar[range.length];
//            [title getCharacters:chars range:range];
//            QString foregroundAppTitle = QString::fromUtf16(chars, range.length);
//            delete[] chars;
}
