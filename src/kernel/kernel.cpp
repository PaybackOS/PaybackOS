#include <tty.hpp>
#include <liballoc.h>

void init_gdt();

extern "C" void _init() {
    terminal_initialize();
    init_gdt();
    print("Hello kernel world!\n");
}