#include <boot/multiboot.h>
#include <tty.h>
#include <stty.h>

void main(int debug) {
    print("Hello, Kernel main\n");
    if (debug == 1) {
        print("Kernel is in debug mode");
        print_serial("Kernel is in debug mode");
    } else {
        print("Kernel is not in debug mode");
    }
}