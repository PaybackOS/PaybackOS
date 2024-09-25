#include <stdint.h>

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
    uint16_t limit;  // Size of the IDT (number of bytes)
    uint32_t base;   // Base address of the IDT
} __attribute__((packed)) idtr_t;

static idtr_t idtr;  // IDT register structure
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];  // Get the descriptor for the vector

    descriptor->isr_low    = (uint32_t)isr & 0xFFFF;  // Lower 16 bits of the ISR address
    descriptor->kernel_cs  = 0x08;  // Kernel code segment selector (adjust based on your GDT)
    descriptor->attributes = flags; // Type and attributes (interrupt gate, DPL, present)
    descriptor->isr_high   = (uint32_t)isr >> 16;  // Higher 16 bits of the ISR address
    descriptor->reserved   = 0;  // Reserved is always 0
}
extern void* isr_stub_table[];  // External ISR stubs

void idt_init(void) {
    idtr.base = (uint32_t)&idt;  // Base address of the IDT
    idtr.limit = (sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS) - 1;  // Size of the IDT

    // Set the first 32 vectors (exceptions) using the ISR stubs
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);  // Interrupt gate, present
    }

    // Load the new IDT
    __asm__ volatile ("lidt %0" : : "m"(idtr));  // Load IDT using lidt instruction

    // Enable interrupts
    __asm__ volatile ("sti");  // Set the interrupt flag
}