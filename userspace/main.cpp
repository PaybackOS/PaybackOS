#include <stdio.hpp>
#include <string.h>

#define debug 1

extern "C" void init_pid_manager();

extern "C" void userspace_c(void) {
    init_pid_manager(); // Start the PID managment system
    if (debug) {
        // Test our malloc system
        void* stringtest = new char[43];
        strcpy((char*)stringtest, "This is being printed from the userspace!\n");
        print((char*)stringtest);
        delete(stringtest);
    }
    while(1) {
    }
}
