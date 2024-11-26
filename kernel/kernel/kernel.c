#include <stdio.h>

// Function prototypes
void switch_to_user_mode();
void show_copyright();

// mb_info is processed in _init so remove it as a parameter for kernel_main
void kernel_main(void) {
    show_copyright();
    // Enter the usermode
    switch_to_user_mode();
    klog(3, "Usermode has exited, this is not supposed to happened");
}

void show_copyright() {
    kprintf("All of this code is licensed under the MIT license https://github.com/PaybackOS/PaybackOS\n");
}
