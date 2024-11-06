#include <stdio.hpp>
#include <tty.hpp>
#include <serial.h>

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

void fullinit() {
    // Initialize kernel components
    terminal_initialize();
    init_serial();
    print_serial("Test");
    show_copyright();
    set_kernel_stack((uintptr_t)(esp0_stack + sizeof(esp0_stack)));
    PIC_init();
    klog(1, "PIC started");
    idt_init();
    klog(1, "IDT loaded");
}