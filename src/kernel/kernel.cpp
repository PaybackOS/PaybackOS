#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>

void init_gdt();
void idt_init(void);

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
    asm("int $0");
}