#include <stdio.hpp>
#include <tty.hpp>
#include <string.h>

void init_gdt();

void klog(int level, char* info) {
    if (level == 1) {
        vga::terminal_setcolor(VGA_COLOR_GREEN);
        vga::print("OK ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        vga::print(info);
    } if (level == 2) {
        vga::terminal_setcolor(VGA_COLOR_LIGHT_RED);
        vga::print("WARN ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        vga::print(info);
    } if (level == 3) {
        vga::terminal_setcolor(VGA_COLOR_RED);
        vga::print("OK ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        vga::print(info);
    }
}

extern "C" void _init() {
    terminal_initialize();
    klog(1, "Terminal started\n");
    init_gdt();
    klog(1, "GDT loaded\n");
}