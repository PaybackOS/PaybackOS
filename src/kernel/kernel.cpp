#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>

void init_gdt();

extern "C" void _init() {
    // Init the VGA interface
    terminal_initialize();
    klog(1, "VGA interface started\n");
    // Init the GDT
    init_gdt();
    klog(1, "GDT loaded\n");
}