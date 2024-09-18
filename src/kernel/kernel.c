#include <boot/multiboot.h>
#include <stdio.h>
#include <stty.h>
#include <debug.h>

void main() {
    printf("Thank you for using PaybackOS\n");
    if(debug()) {
        printf("Number Test: %d\n", 1);
        printf("Hex Test: %x\n", 0xff);
    }
    // Halt the CPU with our shutdown interrupt
    asm("int $0");
}