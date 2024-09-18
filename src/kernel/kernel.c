#include <stdio.h>

void main() {
    // Print out our welcome message
    printf("Thank you for using PaybackOS\n");
    // Halt the CPU with our shutdown interrupt
    asm("int $0");
    // In the case of cli and hlt failing we reboot
    asm("int $1");
}