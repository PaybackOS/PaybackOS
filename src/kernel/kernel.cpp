#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>
#include <serial.h>
#include "multiboot.h"

bool isdebug = false;
bool crashme = false;

extern "C" void switch_to_user_mode();
void fullinit();

extern "C" void _init(multiboot_info_t* mb_info) {
    fullinit(); // Init all components such as VGA text mode and such

    char* cmdline = (char*)(uintptr_t)mb_info->cmdline; // Cast to char pointer

    if (strstr(cmdline, "debug") != NULL) {
        klog(1, "Debug mode is enabled.");
        isdebug = true;
    } if (strstr(cmdline, "crashme") != NULL) {
        crashme = true;
    }

    // Transition to user mode
    klog(1, "Entering usermode");
    switch_to_user_mode();
    klog(3, "Usermode has exited, this is not supposed to happened");
}