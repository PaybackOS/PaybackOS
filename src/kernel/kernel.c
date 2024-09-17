#include <boot/multiboot.h>
#include <stdio.h>
#include <stty.h>
#include <debug.h>

void main() {
    printf("Thank you for using SpiteOS\n");
    if(debug()) {
        printf("Number Test: %d\n", 1);
    }
}