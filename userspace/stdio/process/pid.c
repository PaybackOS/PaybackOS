#include <stddef.h>
#include <stdlib.h>

struct Process {
    int pid;
    struct Process* next;
};

struct Process* process_list = NULL;
int next_pid = 1;  // Start PIDs from 1

void print(const char* str);
void putchar(char c);
void klog(int level, const char* msg);
void printf(const char* format, ...);

// Function to create a new process
int create_process() {
    struct Process* new_process = (struct Process*)malloc(sizeof(struct Process));
    if (!new_process) {
        klog(1, "Failed to allocate memory for new process");
        return -1;  // Indicate failure
    }
    
    new_process->pid = next_pid++;
    new_process->next = process_list;
    process_list = new_process;

    printf("Process created with PID: %d\n", new_process->pid);
    return new_process->pid;  // Return the new PID
}

// Function to destroy a process by PID
int destroy_process(int pid) {
    struct Process* current = process_list;
    struct Process* previous = NULL;

    while (current != NULL) {
        if (current->pid == pid) {
            if (previous == NULL) {
                // We're at the head of the list
                process_list = current->next;
            } else {
                // Bypass the current process
                previous->next = current->next;
            }
            free(current);
            printf("Process with PID %d destroyed\n", pid);
            return 0;  // Success
        }
        previous = current;
        current = current->next;
    }
    
    klog(2, "Process not found");
    return -1;  // Process not found
}

// Function to list all processes
void list_processes() {
    struct Process* current = process_list;
    if (current == NULL) {
        printf("No processes running\n");
        return;
    }

    printf("Currently running processes:\n");
    while (current != NULL) {
        printf("PID: %d\n", current->pid);
        current = current->next;
    }
}

// Example usage
void testpid() {
    int pid1 = create_process();
    int pid2 = create_process();
    list_processes();
    destroy_process(pid1);
    list_processes();
}
