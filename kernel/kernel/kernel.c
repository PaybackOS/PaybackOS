#include <stdio.h>
#include <tty.h>
#include <stdbool.h>
#include <boot/multiboot.h>

// Function prototypes
void switch_to_user_mode();
void show_copyright();

void kernel_main(multiboot_info_t* mb_info) {
    // Show that this software is under public domain
    show_copyright();
    // Enter the usermode
    switch_to_user_mode();
    klog(3, "Usermode has exited, this is not supposed to happened");
}

void show_copyright() {
    kprintf("All of this code is licensed under the MIT license https://github.com/PaybackOS/PaybackOS\n");
}