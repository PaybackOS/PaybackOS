#include <tty.h>
#include <string.h>
#include <stdlib.h>
#include "log.h"

// The main function of our kernel
void main() {
    // Say our kernel has loaded
    log(1, "Kernel started");
    /*
    Test our alloc system
    */
    void* testptr = malloc(5);
    strcpy(testptr, "test");
    if (strcmp(testptr, "test") == 0) {
        log(1, "liballoc working");
    } else if (testptr == NULL) {
        log(3, "Not enough memory for liballoc to use");
    } else {
        log(3, "liballoc failed to allocate memory correctly, halting kernel");
    }
    // Free testptr from the memory
    free(testptr);
}