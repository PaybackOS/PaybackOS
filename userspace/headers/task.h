#ifndef TASK_H
#define TASK_H

// Task structure to represent each task
typedef struct {
    void (*task_func)(void);  // Function pointer to the task
    int active;               // Task state: 0 = inactive, 1 = active
    int task_id;              // Unique task identifier
} task_t;

// Yield control back to the scheduler
void yield(void);
// Start a task by setting it as active
void start_task(void (*task_func)(void));
// Stop a specific task by disabling it
void stop_task(int task_id);
// Remove a task completely by shifting others
void remove_task(int task_id);
// The main cooperative multitasking function (scheduler)
void scheduler(void);

#endif