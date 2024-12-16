#include <print.h>
#include <liballoc.h>
#include <string.h>
#include <task.h>

void testfunc1() {
    print_str("task1\n");
    yield();
}
void testfunc2() {
    print_str("task2\n");
    yield();
}

void test_liballoc() {
    void* ptrtest = malloc(19);
    if (ptrtest == NULL) {
        print_str("liballoc failing.\n");
        asm("cli; hlt");
    } else {
        memcpy(ptrtest, "Liballoc working!\n", 19);
        print_str("Liballoc working!\n");
    }
    free(ptrtest);
}

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_str("Welcome to our 64-bit kernel!\n");
    test_liballoc();
    // Test the scheduler
    add_task(testfunc1);
    add_task(testfunc2);
    scheduler();
}
