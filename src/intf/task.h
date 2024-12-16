#pragma once

// Define a function prototype for all tasks
typedef void (*task_func)();

// Add task function (to dynamically add a task to the task list)
void add_task(task_func task);
// Yield function (gives control back to the scheduler)
void yield();
// Scheduler function (Round-Robin)
void scheduler();