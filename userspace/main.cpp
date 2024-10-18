#include <stdio.hpp>
#include <pid.hpp>
#include <stdbool.h>
#include <fat32.hpp>

struct debug {
    bool debug;     // General debugging
    bool fulldebug; // Extended debugging for crash testing
};

extern "C" void userspace_c(void) {
    init_pid_manager(); // Start the PID management system

    debug debuginfo;
    // Set the debugging flags
    debuginfo.debug = true; // Enable general debugging
    debuginfo.fulldebug = false; // Enable for testing new features for crash prevention

    if (debuginfo.debug) {
        uint8_t buffer[SECTOR_SIZE];  // Buffer for file data

        read_bpb();  // Initialize and read the BPB

        if (read_file("efi.img", buffer, sizeof(buffer)) == 0) {
            print("File read successfully.\n");
            // Process buffer here (e.g., print contents or handle as needed)
        } else {
            print("File not found.\n");
        }
    }

    if (debuginfo.fulldebug) {
        // Test our stack trace
        klog(1, "Testing stack tracing, this GPF is designed to happen.\n");
        asm("cli"); // Trigger a General Protection Fault (GPF)
    }

    // Stop a return to our entry function
    while (1) {
    }
}