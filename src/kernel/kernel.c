#include <stdio.h>
#include <tty.h>
#include <string.h>
#include <serial.h>
#include <stdbool.h>
#include "multiboot.h"

bool isdebug = false;
bool crashme = false;

// Function prototypes
void idt_init(void);
void PIC_init();
void set_kernel_stack(uintptr_t);
void switch_to_user_mode();
void show_copyright();

// Stack for system calls
uint8_t esp0_stack[4096] __attribute__((aligned(4096)));

void _init(multiboot_info_t* mb_info) {
    terminal_initialize();
    // Show that this software is under public domain
    show_copyright();
    // Startup the serial port
    init_serial();
    // Setup the kernel stack for interrupts
    set_kernel_stack((uintptr_t)(esp0_stack + sizeof(esp0_stack)));
    // Init the PIC (Programmable Interrupt Controller)
    PIC_init();
    // Setup the IDT (Interrupt Descriptor Table)
    idt_init();

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

void show_copyright() {
    kprintf("All code and these works are under public domain and available at https://github.com/PaybackOS/PaybackOS\n");
}