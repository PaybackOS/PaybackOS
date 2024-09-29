#include <stdio.hpp>
#include <tty.hpp>

void klog(int level, const char* info) {
    if (level == 1) {
        vga::terminal_setcolor(VGA_COLOR_GREEN);
        vga::print("OK ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf(info);
        vga::putchar('\n');
    } if (level == 2) {
        vga::terminal_setcolor(VGA_COLOR_LIGHT_RED);
        vga::print("WARN ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf(info);
        vga::putchar('\n');
    } if (level == 3) {
        vga::terminal_setcolor(VGA_COLOR_RED);
        vga::print("CRIT ERR ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf(info);
        vga::putchar('\n');
    }
}