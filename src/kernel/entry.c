#include <tty.h>
#include <stty.h>
#include <string.h>
#include <boot/multiboot.h>
#include <boot/kernel.h>

void _init(multiboot_info_t *info) {
    // Initialize bare bones for kernel to run
    terminal_initialize();
    init_serial();
    print("Hello _init\n");

    // Check if the cmdline field is available
    if (info->flags & MULTIBOOT_INFO_CMDLINE) {
        char *cmdline = (char *)info->cmdline;

        // Check for "debug" in the cmdline using strstr
        if (strstr(cmdline, "debug")) {
            main(1);
        } else {
            main(0);
        }
    } else {
        main(0);
    }
}
