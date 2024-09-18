#include <tty.h>
#include <stty.h>
#include <string.h>
#include <boot/multiboot.h>
#include <boot/kernel.h>
#include <debug.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <stdio.h>

// A simple setup to init the OS before it actually starts the real kernel
void _init(multiboot_info_t *info) {
    // Initialize the VGA text mode terminal
    terminal_initialize();
    // Initialize the serial port (not needed in qemu)
    init_serial();
    // Initialize the GDT (needed for IDT)
    init_gdt();
    // Initialize the IDT (needed for interrupts)
    init_idt();
    // Print our hello to our init
    print("Hello _init\n");

    // Check if the cmdline field is available
    if (info->flags & MULTIBOOT_INFO_CMDLINE) {
        char *cmdline = (char *)info->cmdline;

        // Check for "debug" in the cmdline using strstr
        if (strstr(cmdline, "debug")) {
            // Set debug to true
            setdebug(1);
            main();
        } else {
            // Set debug to false
            setdebug(0);
            main();
        }
    } else {
        // Set debug to false
        setdebug(0);
        main();
    }
}
