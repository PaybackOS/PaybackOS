#include <stdint.h>
#include "idtcommon.h"

void init_isr_handlers();
extern void isr_stub_80();  // Declare the ISR stub as extern

typedef struct {
    uint16_t isr_low;      // Lower 16 bits of ISR address
    uint16_t kernel_cs;    // Code segment selector in GDT
    uint8_t  reserved;     // Reserved, always set to 0
    uint8_t  attributes;   // Type and attributes (flags)
    uint16_t isr_high;     // Higher 16 bits of ISR address
} __attribute__((packed)) idt_entry_t;

#define IDT_MAX_DESCRIPTORS 256  // Maximum number of IDT entries

__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];  // Array of IDT entries, aligned for performance

typedef struct {
    uint16_t  limit;  // Size of the IDT (number of bytes)
    uintptr_t base;   // Base address of the IDT
} __attribute__((packed)) idtr_t;

static idtr_t idtr;  // IDT register structure

void idt_set_descriptor(uint8_t vector, uintptr_t isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];  // Get the descriptor for the vector

    descriptor->isr_low    = isr & 0xFFFF;     // Lower 16 bits of the ISR address
    descriptor->kernel_cs  = 0x08;              // Kernel code segment selector
    descriptor->attributes = flags;             // Type and attributes (e.g., 0x8E for interrupt gate)
    descriptor->isr_high   = (isr >> 16) & 0xFFFF;  // Higher 16 bits of the ISR address
    descriptor->reserved   = 0;                  // Reserved is always 0
}

extern void* isr_stub_table[];  // External ISR stubs

void idt_init(void) {
    idtr.base = (uintptr_t)idt;
    idtr.limit = (sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS) - 1;

    // Set up the default stub handlers for all 256 interrupts
    for (uint16_t vector = 0; vector < IDT_MAX_DESCRIPTORS; vector++) {
        idt_set_descriptor(vector, (uintptr_t)isr_stub_table[vector], 0x8E);
    }
    
    //Set syscall DPL=3 to allow "int 80" software interrupt from usermode
    idt_set_descriptor(80, (uintptr_t)isr_stub_table[80], 0x8E | 3 << 5);

    init_isr_handlers();

    // Load the new IDT
    __asm__ volatile ("lidt %0" : : "m"(idtr));

    // Enable interrupts
    __asm__ volatile ("sti");
}
