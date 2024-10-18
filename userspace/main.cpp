#include <stdio.hpp>
#include <string.h>
#include <pid.hpp>
#include <stdbool.h>

struct debug {
    bool debug; // General debugging, testing memory managment and so on
    bool fulldebug; // Extension of debug, used to test stuff like a GPF.
};

extern "C" void userspace_c(void) {
    init_pid_manager(); // Start the PID managment system
    debug debuginfo;
    // Set the debugging flags
    debuginfo.debug = true; // General debugging
    debuginfo.fulldebug = false; // Enable for testing new features for crash prevention and such
    if (debuginfo.fulldebug) {
        // Test our stack trace
        klog(1, "Testing stack tracing, this GPF is designed to happen.\n");
        asm("cli"); // Trigger stack trace from calling a command that is priviledged.
    }
    while(1) {
    }
}
