#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pid.hpp>

extern "C" void userspace_init(void) {
    init_pid_manager(); // Start the PID managment system
    if (checkdebug() == true) {
        void* ptr = malloc(5);
        strcpy((char*)ptr, "test");
        klog(1, (char*)ptr);
        free(ptr);
    }
    while(true) {
        
    }
}
