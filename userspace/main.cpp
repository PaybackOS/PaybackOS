#include <stdio.hpp>
#include <string.h>
#include <pid.hpp>
#include <stdbool.h>
#include <string.h>

struct debug {
    bool debug; // General debugging, testing memory managment and so on
    bool fulldebug; // Extension of debug, used to test stuff like a GPF.
};

extern "C" void userspace_c(void) {
    init_pid_manager(); // Start the PID managment system
    create_pid(0); // Create the userspace PID
    debug debuginfo;
    // Set the debugging flags
    debuginfo.debug = false; // General debugging
    debuginfo.fulldebug = false; // Enable for testing new features for crash prevention and such
    if (debuginfo.debug) {
        char* debugstuff = new char[25];
        strcpy(debugstuff, "Userspace mem alloc test");
        print(debugstuff);
        delete[] debugstuff;
    }
    if (debuginfo.fulldebug) {
        // Test our stack trace
        klog(1, "Testing stack tracing, this GPF is designed to happen.\n");
        asm("cli"); // Trigger stack trace from calling a command that is priviledged.
    }
    print("> ");
    delete_pid(0); // Shut down the userspace since it is no longer active
    while(true) {
        
    }
}
