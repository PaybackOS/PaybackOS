#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>

// When needed use a proper multiboot info structure
struct mb_info_t;

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
    for(constructor* ctor = start_ctors; ctor != end_ctors; ctor++)
        (*ctor)();
}

extern "C" void _init(const mb_info_t* mb_info, uint32_t mb_magic) {
    (void)mb_info;
    (void)mb_magic;

    // Init the VGA interface
    terminal_initialize();
    serial::init_serial();
    klog(1, "VGA interface started");
    // Init the GDT
    init_gdt();
    // Set kernel stack for transitions from usermode
    // This stack is by default set to 0 which is not
    // a usable memory location when it wraps to top of
    // memory.
    set_kernel_stack((uintptr_t)(esp0_stack + sizeof(esp0_stack)));
    klog(1, "GDT loaded");
    // Init the PIC before idt_init!
    PIC_init();
    klog(1, "PIC started");
    // Init the IDT
    idt_init();
    klog(1, "IDT loaded");
    // Move to our userspace
    switch_to_user_mode();
}
