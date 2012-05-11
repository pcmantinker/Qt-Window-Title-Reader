#import "Cocoa/Cocoa.h"

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
                QString foregroundAppTitle = qt_mac_NSStringToQString(title);
                qDebug() << foregroundAppTitle;
                i++;
        }
}
