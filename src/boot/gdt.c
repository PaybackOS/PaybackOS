#include <stdint.h>

// GDT Entry structure
typedef struct {
    uint16_t limit_low;   // Lower 16 bits of the limit
    uint16_t base_low;    // Lower 16 bits of the base address
    uint8_t base_middle;  // Next 8 bits of the base address
    uint8_t access;       // Access flags
    uint8_t granularity;  // Granularity and upper 4 bits of the limit
    uint8_t base_high;    // Upper 8 bits of the base address
} __attribute__((packed)) gdt_entry_t;

// GDT Pointer structure
typedef struct {
    uint16_t limit;       // Size of the GDT in bytes
    uint32_t base;        // Base address of the GDT
} __attribute__((packed)) gdt_pointer_t;

// Function to load the GDT using inline assembly
void load_gdt(gdt_pointer_t* gdt_ptr) {
    __asm__ volatile (
        "lgdt (%0)"   // Load the GDT
        :
        : "r"(gdt_ptr)  // Input operand
        : "memory"    // Clobbered register
    );
}

// GDT Entries
gdt_entry_t gdt[3];
gdt_pointer_t gdt_ptr;

// Function to set a GDT entry
void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = (limit >> 16) & 0x0F;
    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}

// Function to initialize the GDT
void init_gdt() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_ptr.base = (uint32_t) &gdt;

    // Null descriptor
    gdt_set_entry(0, 0, 0, 0, 0);

    // Kernel code segment descriptor
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);

    // Kernel data segment descriptor
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

    // Load the GDT
    load_gdt(&gdt_ptr);
}