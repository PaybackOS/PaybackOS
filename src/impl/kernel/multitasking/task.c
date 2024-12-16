#define MAX_FUNCTIONS 10  // Maximum number of functions

// Define a function prototype for all tasks
typedef void (*task_func)();

// Task list and number of active tasks
task_func tasks[MAX_FUNCTIONS]; 
int num_tasks = 0;  // Keeps track of how many tasks have been added

// Current task index, used for round-robin scheduling
int current_task = 0;

// Add task function (to dynamically add a task to the task list)
void add_task(task_func task) {
    if (num_tasks < MAX_FUNCTIONS) {
        tasks[num_tasks++] = task;  // Add task and increment number of tasks
    }
}

// Yield function (gives control back to the scheduler)
void yield() {
    // Move to the next task, wrapping around when reaching the end
    current_task = (current_task + 1) % num_tasks;
}

// Scheduler function (Round-Robin)
void scheduler() {
    while (1) {  // Run forever or until externally stopped
        // Call the current task function
        tasks[current_task]();
    }
}
