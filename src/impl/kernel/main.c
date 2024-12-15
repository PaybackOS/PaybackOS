#include <print.h>
#include <liballoc.h>
#include <string.h>

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_str("Welcome to our 64-bit kernel!\n");
    void* ptrtest = malloc(19);
    if (ptrtest == NULL) {
        print_str("liballoc failing.\n");
    } else {
        memcpy(ptrtest, "Liballoc working!\n", 19);
        print_str("Liballoc working!\n");
    }
    free(ptrtest);
}
