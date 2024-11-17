#include <stdio.h>
#include <stdbool.h>
#include <tty.h>

extern bool isdebug;

void klog(int level, const char* info) {
    if (level == 0 && isdebug) {
        terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
        print("Debug ");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf("%s\n", info);
    } else if (level) {
        terminal_setcolor(VGA_COLOR_GREEN);
        print("OK ");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf("%s\n", info);
    } if (level == 2) {
        terminal_setcolor(VGA_COLOR_LIGHT_RED);
        print("WARN ");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        kprintf("%s\n", info);
    } if (level == 3) {
        terminal_setcolor(VGA_COLOR_RED);
        print("CRIT ERR ");
        kprintf("%s\n", info);
        asm("cli; hlt");
    }
}