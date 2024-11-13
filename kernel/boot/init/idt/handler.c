#include <tty.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "port.h"
#include "idtcommon.h"

void register_isr_handler(uint8_t num, isr_t handler);
void syscall_handler(stack_frame_t *frame);
void key_translate(uint8_t scancode);

isr_t isr_dispatch_table[256] = { NULL };

const char *exception_descriptions[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void register_isr_handler(uint8_t num, isr_t handler)
{
    if (num < sizeof(isr_dispatch_table)/sizeof(*isr_dispatch_table))
        isr_dispatch_table[num] = handler;

    return;
}
void __attribute__((noreturn)) default_exception_handler(stack_frame_t *frame)
{
    if (frame->int_num < sizeof(exception_descriptions)/sizeof(*exception_descriptions))
        klog(3, exception_descriptions[frame->int_num]);
    else
        klog(3, "Unknown exception");

    klog(3, "Halting Kernel");
}

void send_eoi(uint8_t irq)
{
    // Send EOI to master and slave if necessary
    if (irq >= 8)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
    return;
}

void default_irq_handler(stack_frame_t *frame)
{
    uint8_t irq_number = frame->int_num - 32;
    klog(1, "External Interrupt Received");

    send_eoi(irq_number);
    return;
}


void keyboard_handler(stack_frame_t *frame) {
    uint8_t irq_number = frame->int_num - 32;

    // Retrive scancode from keyboard buffer.
    uint8_t scancode = inb(0x60);
    key_translate(scancode);
    
    send_eoi(irq_number);
    return;
}

void __attribute__((noreturn)) divbyzero_handler(stack_frame_t *frame) {
    (void)frame;
    klog(3, exception_descriptions[frame->int_num]);
}

void init_isr_handlers() {
    for (int index = 0; index < 256; index++)
        isr_dispatch_table[index] = default_exception_handler;

    for (int index = 32; index < 48; index++)
        isr_dispatch_table[index] = default_irq_handler;
    register_isr_handler(33, keyboard_handler);
    register_isr_handler(80, syscall_handler);
}

void print_stack_trace() {
    void **stack_ptr;
    asm volatile("mov %%esp, %0" : "=r"(stack_ptr));  // Get current stack pointer

    kprintf("Stack trace:\n");
    for (int i = 0; stack_ptr && i < 10; ++i) {  // Limit to 10 frames
        kprintf("%x\n", (uintptr_t)*stack_ptr); // Print address as hex using %x
        stack_ptr++;
    }
}

bool is_exception(int int_num) {
    return int_num >= 0 && int_num < 32; // Checks if it's any exception (0-31)
}

void C_handler(stack_frame_t *frame) {
    if (frame->int_num >= 256) {
        klog(3, "Invalid interrupt number");
    }

    if (is_exception(frame->int_num)) {
        print_stack_trace(); // Print the stack trace
    }

    if (isr_dispatch_table[frame->int_num] == NULL) {
        klog(3, "No handler registered");
    }

    isr_dispatch_table[frame->int_num](frame);
}