#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pid.h>

extern "C" void userspace_init(void) {
    init_pid_manager(); // Start the PID managment system
    create_pid(0); // Create the userspace PID it should not be killed
    if (checkdebug() == true) {
        void* ptr = malloc(12);
        strcpy((char*)ptr, "malloc test");
        klog(1, (char*)ptr);
        free(ptr);
    } else if (fulldebug() == true) {
        asm("cli");
    }
    while(true) {
        
    }
    delete_pid(0); // only do if while loop fails
}
