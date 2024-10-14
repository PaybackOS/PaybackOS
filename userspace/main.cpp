#include <stdio.hpp>
#include <string.h>

#define debug 1

extern "C" int testpid();

extern "C" void userspace_c(void) {
    if (debug) {
        // Test our malloc system
        void* stringtest = new char[43];
        strcpy((char*)stringtest, "This is being printed from the userspace!\n");
        print((char*)stringtest);
        delete(stringtest);
        // Test our PID system
        testpid();
    }
    while(1) {
    }
}
