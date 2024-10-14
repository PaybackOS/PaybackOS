#include <stddef.h>
#include <stdlib.h>

void print(const char* str);
void putchar(char c);
void klog(int level, const char* msg);
void printf(const char* format, ...);

struct Process {
    int pid;
    struct Process* next;
};

struct Process* head = NULL;

int createProcess(int pid) {
    struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
    if (newProcess == NULL) {
        return -1; // Allocation failed
    }

    // Check if the PID is already in use
    struct Process* temp = head;
    while (temp != NULL) {
        if (temp->pid == pid) {
            return -2; // PID already in use
        }
        temp = temp->next;
    }

    // Ensure PID is a positive integer
    if (pid <= 0) {
        return -3; // Invalid PID
    }

    newProcess->pid = pid;
    newProcess->next = NULL; // Always set the next pointer to NULL for new processes

    if (head == NULL) {
        head = newProcess;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newProcess;
    }

    return 0; // Success
}

void terminateProcess(int pid) {
    struct Process* current = head;
    struct Process* previous = NULL;

    while (current != NULL && current->pid != pid) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        // Process not found
        return;
    }

    // Remove the process from the linked list
    if (previous == NULL) {
        // Process is the head
        head = current->next;
    } else {
        previous->next = current->next;
    }

    // Free the memory allocated for the process
    free(current);
}

void printProcessList() {
    print("\nProcess List:\n");
    struct Process* temp = head;
    while (temp != NULL) {
        // Use printf with %d format specifier
        printf("PID: %d\n", temp->pid);

        temp = temp->next;
    }
}

int testpid() {
    // Create a few processes
    int pid1 = createProcess(1);
    int pid2 = createProcess(2);
    int pid3 = createProcess(3);

    if (pid1 == -1 || pid2 == -1 || pid3 == -1) {
        print("PID process creation failed.");
    }

    // Print the process list
    printProcessList();

    // Kill all the processes we just created
    terminateProcess(pid1);
    terminateProcess(pid2);
    terminateProcess(pid3);

    // List the remaining processes
    printProcessList();

    return 0;
}