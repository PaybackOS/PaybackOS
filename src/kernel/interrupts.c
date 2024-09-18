#include <cpu/idt.h>
#include <cpu/port.h>
#include <stdio.h>

// The halt CPU function
void halt_cpu(void) {
    printf("Halting CPU.\n");
    while (1) {
        asm("cli");
        asm("hlt");
    }
}

void reboot() {
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    asm("int $0");
}

void interrupt_setup() {
    idt_set_entry(0, halt_cpu, 0x08, 0x8E);
    idt_set_entry(1, reboot, 0x08, 0x8E);
}