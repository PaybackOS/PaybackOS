#include <stdio.h>  // Assuming tty.h defines putchar() and print(char*)

#define MAX_TASKS 10  // Maximum number of tasks we can handle

// Task structure to represent each task
typedef struct {
    void (*task_func)(void);  // Function pointer to the task
    int active;               // Task state: 0 = inactive, 1 = active
    int task_id;              // Unique task identifier
} task_t;

// Global array of tasks
task_t tasks[MAX_TASKS];
int num_tasks = 0;  // The number of tasks currently in the system
volatile int current_task = 0;  // Index of the currently running task

// Simple delay function to simulate work being done by tasks
void delay(int count) {
    while (count-- > 0) {
        // Just a simple loop to burn CPU cycles (a very naive "delay")
    }
}

// Yield control back to the scheduler
void yield(void) {
    // Advance to the next task in the round-robin scheduler
    do {
        current_task = (current_task + 1) % num_tasks;
    } while (tasks[current_task].active == 0);  // Skip inactive tasks
}

// Start a task by setting it as active
void start_task(void (*task_func)(void)) {
    if (num_tasks < MAX_TASKS) {
        tasks[num_tasks].task_func = task_func;
        tasks[num_tasks].active = 1;  // Set task as active
        tasks[num_tasks].task_id = num_tasks;
        num_tasks++;
    }
}

// Stop a specific task by disabling it
void stop_task(int task_id) {
    if (task_id >= 0 && task_id < num_tasks) {
        tasks[task_id].active = 0;  // Mark task as inactive
    }
}

// Remove a task completely by shifting others
void remove_task(int task_id) {
    if (task_id >= 0 && task_id < num_tasks) {
        // Shift tasks down
        for (int i = task_id; i < num_tasks - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        num_tasks--;
    }
}

// The main cooperative multitasking function (scheduler)
void scheduler(void) {
    while (1) {
        if (num_tasks > 0) {
            tasks[current_task].task_func();  // Execute the current task
        } else {
            user_print("No tasks to execute.\n");
            break;  // No tasks available, exit the scheduler
        }
    }
}