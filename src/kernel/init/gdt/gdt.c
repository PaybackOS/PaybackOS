#include <stdint.h>
#include <stddef.h>

// Structure for a GDT entry (8 bytes)
struct GDTEntry {
    uint16_t limit_low;    // Lower 16 bits of the limit
    uint16_t base_low;     // Lower 16 bits of the base
    uint8_t  base_middle;  // Middle 8 bits of the base
    uint8_t  access;       // Access flags
    uint8_t  granularity;  // Granularity and higher limit
    uint8_t  base_high;    // Higher 8 bits of the base
} __attribute__((packed));

// Structure for the GDT pointer (used by the lgdt instruction)
struct GDTPointer {
    uint16_t limit;        // Size of the GDT minus 1
    uintptr_t base;        // Base address of the GDT
} __attribute__((packed));

// Structure for the Task State Segment (TSS)
struct TSS {
    uint32_t prev_tss;      // Previous TSS (not used)
    uint32_t esp0;          // Stack pointer to load when switching to kernel mode
    uint32_t ss0;           // Stack segment for kernel mode
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed));

struct TSS tss;  // Declare a global TSS

// GDT with 6 entries: Null, Kernel Code, Kernel Data, User Code, User Data, TSS
struct GDTEntry gdt[6];
struct GDTPointer gdtp;

// Function to set a GDT entry
void set_gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[num].base_low    = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high   = (base >> 24) & 0xFF;

    gdt[num].limit_low   = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (granularity & 0xF0);
    gdt[num].access      = access;
}

// Function to load the GDT (using inline assembly)
void gdt_flush(uint32_t gdt_ptr) {
    __asm__ __volatile__ (
        "lgdt (%0)\n"           // Load the GDT pointer
        "mov $0x10, %%ax\n"     // Kernel data segment (0x0010)
        "mov %%ax, %%ds\n"      // Load DS register
        "mov %%ax, %%es\n"      // Load ES register
        "mov %%ax, %%fs\n"      // Load FS register
        "mov %%ax, %%gs\n"      // Load GS register
        "mov %%ax, %%ss\n"      // Load SS register
        "jmp $0x08, $1f\n"      // Far jump to reload CS with kernel code segment (0x0008)
        "1:\n"                  // Numeric label 1
        :                       // No output operands
        : "r" (gdt_ptr)         // Input operand (the GDT pointer)
        : "ax"                  // Clobbered register (ax)
    );
}

// Function to load the TSS (using inline assembly)
void tss_flush(uint16_t tss_segment_selector) {
    __asm__ __volatile__ (
        "ltr %0\n"              // Load the TSS segment selector into the Task Register (TR)
        :
        : "r" (tss_segment_selector)  // Input operand (TSS segment selector)
    );
}

// Initialize the GDT and TSS
void init_gdt() {
    // Null descriptor (0x0000)
    set_gdt_entry(0, 0, 0, 0, 0);

    // Kernel Code Segment (0x0008)
    set_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xC0);

    // Kernel Data Segment (0x0010)
    set_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xC0);

    // User Code Segment (0x0018)
    set_gdt_entry(3, 0, 0xFFFFF, 0xFA, 0xC0);

    // User Data Segment (0x0020)
    set_gdt_entry(4, 0, 0xFFFFF, 0xF2, 0xC0);

    // Task State Segment (0x0028)
    set_gdt_entry(5, (uintptr_t)&tss, sizeof(tss) - 1, 0x89, 0x00);

    // Update the GDT pointer
    gdtp.limit = (sizeof(gdt) - 1);
    gdtp.base  = (uintptr_t)&gdt;

    // Flush the new GDT
    gdt_flush((uintptr_t)&gdtp);

    // Initialize the TSS
    tss.ss0  = 0x10;    // Kernel data segment selector
    tss.esp0 = 0;       // Set the stack pointer later with your bootloader's stack
    tss.iomap_base = sizeof(tss);  // No I/O map

    // Flush the TSS (load it into the TR)
    tss_flush(0x28);  // 0x28 is the GDT entry selector for the TSS
}

// Function to set the kernel stack in TSS (uses the stack already provided by the bootloader)
void set_kernel_stack(uintptr_t stack) {
    tss.esp0 = stack;  // Set esp0 to the top of your bootloader-provided stack
}
