#ifndef PID_H
#define PID_H

#ifdef __cplusplus
extern "C" {
#endif

// Initialize the PID management system
void init_pid_manager();

// Create a new PID
int create_pid(int requested_pid);

// Delete a PID
void delete_pid(int pid);

#ifdef __cplusplus
}
#endif

#endif // PID_H
