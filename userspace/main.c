#include <stdio.h>
#include <stdbool.h>
#include <task.h>

void task1() {
    putchar('A');
    yield();
}

void task2() {
    putchar('B');
    yield();
}

void userspace_init(void) {
    start_task(task1);
    start_task(task2);
    scheduler();
    while (1);
}
