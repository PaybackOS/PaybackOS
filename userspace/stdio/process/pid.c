#include <stdio.h>
#include <pid.h>

#define MAX_PROCESSES 256

struct pid {
    int pid;
    int in_use;
};

struct pid programs[MAX_PROCESSES];

// Initialize the PID management system
void init_pid_manager() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        programs[i].pid = -1;  // Set all PIDs to an invalid state
        programs[i].in_use = 0; // Mark as not in use
    }
}

// Create a new PID
int create_pid(int requested_pid) {
    if (requested_pid < 0 || requested_pid >= MAX_PROCESSES) {
        klog(3, "Invalid PID requested");
        return -1;
    }

    // Check for an available PID instead of checking if the requested one is in use
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (!programs[i].in_use) {
            programs[i].pid = requested_pid;
            programs[i].in_use = 1; // Mark as in use
            return requested_pid;
        }
    }

    klog(3, "No available PIDs to create");
    return -1;
}

// Delete a PID
void delete_pid(int pid) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (programs[i].in_use && programs[i].pid == pid) {
            programs[i].in_use = 0; // Mark as not in use
            programs[i].pid = -1;   // Reset the PID to an invalid state
            return;
        }
    }

    klog(3, "Attempted to delete non-existent or invalid PID");
}
