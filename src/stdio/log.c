#include <tty.h>

/*
A simple logging function

Log level 1 is OK or nothing is broken
Log level 2 is WARN or a warning that something may be broken but it is not known
Log level 3 is ERROR or a error that is something is broken and the OS will no longer be able to work
*/
void log(int level, char* effect) {
    if (level == 1) {
        terminal_setcolor(VGA_COLOR_GREEN);
        print("OK ");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        print(effect);
        putchar('\n');
    } else if (level == 2) {
        terminal_setcolor(VGA_COLOR_BROWN);
        print("WARN ");
        print(effect);
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
        putchar('\n');
    } else if (level == 3) {
        terminal_setcolor(VGA_COLOR_LIGHT_RED);
        print("ERROR ");
        print(effect);
        putchar('\n');
        asm("cli");
        asm("hlt");
    }
}