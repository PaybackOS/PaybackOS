#include <stdio.h>
#include <liballoc.h>
#include <string.h>
#include <task.h>
#include <stdbool.h>

bool debug = true;

void testfunc1() {
    static int itr = 0;  // Retains value across invocations
    if (itr == 2) {
        end_task();
        return;  // Exit the function after removing the task
    }
    printf("task1\n");
    itr++;
    yield();
}

void testfunc2() {
    static int itr = 0;  // Retains value across invocations
    if (itr == 2) {
        end_task();
        return;  // Exit the function after removing the task
    }
    printf("task2\n");
    itr++;
    yield();
}

void test_liballoc() {
    void* ptrtest = malloc(19);
    if (ptrtest == NULL) {
        printf("liballoc failing.\n");
        asm("cli; hlt");
    } else {
        memcpy(ptrtest, "Liballoc working!\n", 19);
        printf("Liballoc working!\n");
    }
    free(ptrtest);
}

void kernel_main() {
    printf("Thank you for using PaybackOS!\n");
    if (debug == true) {
        // Test our memory allocation
        test_liballoc();
        // Test the scheduler
        add_task(testfunc1);
        add_task(testfunc2);
        scheduler();
    }
    // Test the logging system
    log(DEBUG, "debug test.");
}
