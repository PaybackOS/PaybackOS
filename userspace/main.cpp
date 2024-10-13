#include <stdio.hpp>
#include <string.h>

#define debug 1

extern "C" void userspace_c(void) {
    if (debug) {
        klog(1, "test log from userspace");
        void* stringtest = new char[43];
        strcpy((char*)stringtest, "This is being printed from the userspace!\n");
        print((char*)stringtest);
        delete(stringtest);
    }

    while(1) {
    }
}
