#include <boot/multiboot.h>
#include <stdio.h>
#include <stty.h>
#include <debug.h>

void main() {
    // Print out our welcome message
    printf("Thank you for using PaybackOS\n");
    // Check if we are in debug mode
    if(debug()) {
        printf("Number Test: %d\n", 1);
        printf("Hex Test: %x\n", 0xff);
    }
    // Halt the CPU with our shutdown interrupt
    asm("int $0");
    // In the case of cli and hlt failing we reboot
    asm("int $1");
}