#include <tty.hpp>
#include <liballoc.h>
#include <string.h>

void init_gdt();

extern "C" void _init() {
    terminal_initialize();
    init_gdt();
    void* ptrtest = malloc(22);
    print("Hello kernel world!\n");
}