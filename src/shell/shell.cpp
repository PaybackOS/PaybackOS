#include <stdbool.h>
#include <string.h>
#include <tty.hpp>
#include <stdio.hpp>

// Debug shell
void execute_command(char *input) {
    if (strcmp(input, "EXIT") == 0) {
        klog(1, "SHUTTING DOWN CPU!\n");
        asm("cli; hlt");
    }
    return;
}