#include <cpu/idt.h>
#include <cpu/port.h>
#include <stdio.h>

volatile uint32_t ms_ticks = 0; // Millisecond counter

// The halt CPU function
void halt_cpu(void) {
    printf("Halting CPU.\n");
    while (1) {
        asm("cli");
        asm("hlt");
    }
    // if it breaks from our infinite loop it will reboot
    asm("int $1");
}

void reboot() {
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    asm("int $0");
}

void interrupt_setup() {
    idt_set_entry(0, halt_cpu, 0x08, 0x8E); // Interrupt for halt
    idt_set_entry(1, reboot, 0x08, 0x8E);   // Interrupt for reboot
}
