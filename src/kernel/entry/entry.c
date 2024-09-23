#include <tty.h>
#include <string.h>
#include <boot/multiboot.h>
#include <boot/kernel.h>
#include <debug.h>
#include <stdio.h>

// A simple setup to init the OS before it actually starts the real kernel
void _init(multiboot_info_t *info) {
    // Initialize the VGA text mode terminal
    terminal_initialize();

    main();
}
