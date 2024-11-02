#include <stdbool.h>
#include <string.h>
#include <tty.hpp>
#include <stdio.hpp>
#include <port.h>

// Function prototypes
void term_help();

void halt() {
    klog(1, "SHUTTING DOWN CPU!\n");
    asm("cli; hlt");
}

void reboot() {
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    halt();
}

// Debug shell (kernel space)
void execute_command(char *input) {
    if (strcmp(input, "EXIT") == 0) {
        // Clear the screen and halt the CPU
        clear_terminal();
        halt();
    } else if (strcmp(input, "REBOOT") == 0) {
        // Do a 8042 (PS/2 controller) reboot
        reboot();
    } else if (strcmp(input, "CLEAR") == 0) {
        // Clear the screen
        clear_terminal();
    } else if (strcmp(input, "HELP") == 0) {
        term_help();
    } else if (strcmp(input, "") == 0) {
        asm("nop"); // Do nothing
    } else {
        kprintf("Command %s is not a command\n", input);
    }
    kprintf("> ");
    return;
}

void term_help() {
    kprintf("EXIT: shutdown the CPU.\n");
    kprintf("REBOOT: Tell the 8042 PS/2 chip to reboot the system.\n");
    kprintf("HELP: List these commands\n");
}