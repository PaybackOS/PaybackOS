#include <stdio.h>
#include <tty.h>
#include <string.h>
#include <stdbool.h>
#include "multiboot.h"

bool isdebug = false;

// Function prototypes
void switch_to_user_mode();
void show_copyright();

void kernel_main(multiboot_info_t* mb_info) {
    char* cmdline = (char*)(uintptr_t)mb_info->cmdline; // Cast to char pointer

    if (strstr(cmdline, "debug") != NULL) {
        isdebug = true;
    }
    // Show that this software is under public domain
    show_copyright();
    // Enter the usermode
    switch_to_user_mode();
    klog(3, "Usermode has exited, this is not supposed to happened");
}

void show_copyright() {
    kprintf("All code and these works are under public domain and available at https://github.com/PaybackOS/PaybackOS\n");
}