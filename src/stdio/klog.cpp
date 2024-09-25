#include <stdio.hpp>
#include <tty.hpp>

void klog(int level, const char* info) {
    if (level == 1) {
        vga::terminal_setcolor(VGA_COLOR_GREEN);
        vga::print("OK ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        printf(info);
    } if (level == 2) {
        vga::terminal_setcolor(VGA_COLOR_LIGHT_RED);
        vga::print("WARN ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        printf(info);
    } if (level == 3) {
        vga::terminal_setcolor(VGA_COLOR_RED);
        vga::print("OK ");
        vga::terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        printf(info);
    }
}