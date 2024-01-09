#include <stdio.h>
#include <ApplicationServices/ApplicationServices.h>

CGEventRef MyEventTapCallBack (CGEventTapProxy proxy, CGEventType type, CGEventRef ref, void *udref) {
    printf("Event %d %d\n", type, (*(int*)udref));
    return NULL;
}

int main(int argc, const char * argv[]) {
    int userData = 42;
    //CGEventMask mask = CGEventMaskBit(kCGEventKeyUp) | CGEventMaskBit(kCGEventKeyDown);
    CGEventMask mask = kCGEventMaskForAllEvents;
    CFMachPortRef port = CGEventTapCreate(kCGHIDEventTap, kCGHeadInsertEventTap, kCGEventTapOptionListenOnly, mask, MyEventTapCallBack, &userData);

    if (port == NULL) {
        printf("Invalid Mach Port");
        return 1;
    }

    CFRunLoopSourceRef loopref = CFMachPortCreateRunLoopSource(NULL, port, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), loopref, kCFRunLoopDefaultMode);

    printf("Listening for events (CGEventTapCreate)...\n");

    CFRunLoopRun();

    return 0;
}

