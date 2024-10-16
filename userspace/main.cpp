#include <stdio.hpp>
#include <string.h>

struct debug {
    int debug; // General debugging, testing memory managment and so on
    int fulldebug; // Extension of debug, used to test stuff like a GPF.
};
extern "C" void init_pid_manager();

extern "C" void userspace_c(void) {
    init_pid_manager(); // Start the PID managment system
    debug debuginfo;
    // Set the debugging flags
    debuginfo.debug = 1;
    debuginfo.fulldebug = 0; // Enable for testing new features for crash prevention and such
    if (debuginfo.debug || debuginfo.fulldebug) {
        // Test our malloc system
        void* stringtest = new char[43];
        strcpy((char*)stringtest, "This is being printed from the userspace!\n");
        print((char*)stringtest);
        delete(stringtest);
        if (debuginfo.fulldebug) {
            // Test our stack trace
            printf("This GPF is MEANT to happen\n");
            asm("cli"); // Trigger the GPF due to attempting to run privilidged command
        }
    }
    while(1) {
    }
}
