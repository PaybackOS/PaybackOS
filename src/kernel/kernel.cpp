#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>

void init_gdt();
void idt_init(void);
void PIC_init();
extern "C" void switch_to_user_mode();

extern "C" void _init() {
    // Init the VGA interface
    terminal_initialize();
    klog(1, "VGA interface started");
    // Init the GDT
    init_gdt();
    klog(1, "GDT loaded");
    // Init the IDT
    idt_init();
    klog(1, "IDT loaded");
    // Init the PIC
    PIC_init();
    klog(1, "PIC started");
    //Move to our userspace
    switch_to_user_mode();
}