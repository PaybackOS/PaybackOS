#include <stdio.h>
#include <tty.h>

void klog(int level, const char* info) {
    if (level == 1) {
        terminal_setcolor(VGA_COLOR_GREEN);
        print("OK ");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf(info);
        putchar('\n');
    } if (level == 2) {
        terminal_setcolor(VGA_COLOR_LIGHT_RED);
        print("WARN ");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf(info);
        putchar('\n');
    } if (level == 3) {
        terminal_setcolor(VGA_COLOR_RED);
        print("CRIT ERR ");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf(info);
        putchar('\n');
    }
}