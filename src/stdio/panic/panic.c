#include <stdio.h>

void panic(int error) {
    printf("Kernel panic! shutting down system, error code: %d", error);
    asm("int $0");
}