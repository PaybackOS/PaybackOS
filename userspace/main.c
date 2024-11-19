#include <stdio.h>
#include <stdbool.h>
#include <task.h>

void task1() {
    
}

void userspace_init(void) {
    if (checkdebug() == true) {
        asm("cli");
        log(1, "This is a message from the userspace");
    }
    while (1);
}
