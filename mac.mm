#include "mac.h"

#import "Cocoa/Cocoa.h"
void Mac::getWindowTitle()
{
    int i =0;
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSMutableArray *windows = (NSMutableArray *)CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements, kCGNullWindowID);

    for (NSDictionary *window in windows) {
        NSString *owner = [window objectForKey:@"kCGWindowOwnerName" ];
        NSString *name = [window objectForKey:@"kCGWindowName" ];
        NSNumber *layer = [window objectForKey:@"kCGWindowLayer"];

        if([layer intValue] == 0 && i == 0){/* only returns the first window title.
Window titles are returned are in order from front to back and i only want the
frontmost active window title.*/
            NSString *title =  [owner stringByAppendingString:@" - "];
            title = [title stringByAppendingString:name];

            NSRange range;
            range.location = 0;
            range.length = [title length];
//            QString result(range.length, QChar(0));

            unichar *chars = new unichar[range.length];
            [title getCharacters:chars range:range];
            QString foregroundAppTitle = QString::fromUtf16(chars, range.length);
            delete[] chars;
            qDebug() << foregroundAppTitle;
            i++;
        }
    }
}
