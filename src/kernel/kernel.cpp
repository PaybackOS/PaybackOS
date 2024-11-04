#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>
#include "multiboot.h"

bool isdebug = false;

void init_gdt();
void idt_init(void);
void PIC_init();
void set_kernel_stack(uintptr_t);

uint8_t esp0_stack[4096] __attribute__((aligned(4096)));
extern "C" void switch_to_user_mode();

typedef void (*constructor)();
extern "C" constructor start_ctors[];
extern "C" constructor end_ctors[];

// Function to iterate through all global constructors and
// call them. This must be done befor calling _init
extern "C" void call_constructors()
{
    size_t n = ((uintptr_t)end_ctors - (uintptr_t)start_ctors)/(sizeof(constructor));
    for (constructor *ctor = start_ctors; ctor < start_ctors + n; ctor++)
        (*ctor)();
}

void show_copyright() {
    kprintf("All code and these works are under public domain and available at https://github.com/PaybackOS/PaybackOS\n");
}

extern "C" void _init(multiboot_info_t* mb_info) {
    // Initialize kernel components
    terminal_initialize();
    show_copyright();
    set_kernel_stack((uintptr_t)(esp0_stack + sizeof(esp0_stack)));
    PIC_init();
    klog(1, "PIC started");
    idt_init();
    klog(1, "IDT loaded");

    // Directly access cmdline
    char* cmdline = (char*)(uintptr_t)mb_info->cmdline; // Cast to char pointer

    // Check for the "debug" flag in the command line
    if (strstr(cmdline, "debug") != NULL) {
        klog(1, "Debug mode is enabled.");
        isdebug = true;
    } else {
        klog(1, "Debug mode is not enabled.");
    }

    // Transition to user mode
    klog(1, "Transitioning to user mode...");
    switch_to_user_mode();
    klog(1, "User mode transition completed.");
}