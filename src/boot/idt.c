#include <stdint.h>
#include "idtsetup.h"

// IDT Entry structure
typedef struct {
    uint16_t offset_low;   // Lower 16 bits of the interrupt handler offset
    uint16_t selector;     // Selector in the GDT
    uint8_t  zero;         // Reserved, should be zero
    uint8_t  type_attr;    // Type and attributes
    uint16_t offset_high;  // Upper 16 bits of the interrupt handler offset
} __attribute__((packed)) idt_entry_t;

// IDT Pointer structure
typedef struct {
    uint16_t limit;        // Size of the IDT in bytes
    uint32_t base;         // Base address of the IDT
} __attribute__((packed)) idt_pointer_t;

// IDT Entries
idt_entry_t idt[256];
idt_pointer_t idt_ptr;

// Function to set an IDT entry
void idt_set_entry(int num, void (*handler)(void), uint16_t selector, uint8_t type_attr) {
    idt[num].offset_low = (uint32_t)handler & 0xFFFF;
    idt[num].offset_high = ((uint32_t)handler >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
}

// Function to load the IDT using inline assembly
void load_idt(idt_pointer_t* idt_ptr) {
    __asm__ volatile (
        "lidt (%0)"   // Load the IDT
        :
        : "r"(idt_ptr)  // Input operand
        : "memory"    // Clobbered register
    );
}


// Function to initialize the IDT
void init_idt() {
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base = (uint32_t) &idt;

    // Set up interrupts
    interrupt_setup();

    // Load the IDT
    load_idt(&idt_ptr);

    // Enable interrupts
    asm("sti");
}
