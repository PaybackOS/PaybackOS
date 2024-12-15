#include <print.h>

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_str("Welcome to our 64-bit kernel!\nTest");
}
