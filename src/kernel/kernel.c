#include <tty.h>

void main() {
    terminal_setcolor(VGA_COLOR_GREEN);
    print("OK ");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    print("Kernel started");
}