#include <stdio.hpp>
#include <string.h>

#define debug 1

extern "C" void userspace_c(void) {
    print("This is being printed from the userspace!\n");
    if (debug) {
        klog(1, "test log from userspace");
        void* stringtest = new char[5];
        strcpy((char*)stringtest, "hi!\n");
        print((char*)stringtest);
        delete(stringtest);
    }

    while(1) {
    }
}
