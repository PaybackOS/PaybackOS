#ifndef PID_HPP
#define PID_HPP
#pragma once

extern "C" {
    // Initialize the PID management system
    void init_pid_manager();

    // Create a new PID
    int create_pid(int requested_pid);

    // Delete a PID
    void delete_pid(int pid);
}

#endif