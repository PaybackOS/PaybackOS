#include <boot/multiboot.h>
#include <tty.h>
#include <stty.h>
#include <debug.h>

void main() {
    print("Hello, Kernel main\n");
    if (debug()) {
        print("Kernel is in debug mode");
        print_serial("Kernel is in debug mode");
    } else {
        print("Kernel is not in debug mode");
    }
}