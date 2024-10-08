#include <tty.hpp>
#include <stdio.hpp>
#include <stdint.h>
#include "port.h"
#include "keyhandler.h"
#include "idtcommon.hpp"

void register_isr_handler(uint8_t num, isr_t handler);
void syscall_handler(stack_frame_t *frame);
char getch();

isr_t isr_dispatch_table[256] = { nullptr };

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

char getstr(char *buffer, size_t max_size) {
    size_t i = 0;
    char ch;

    while (i < max_size - 1) { // Leave space for null terminator
        ch = getch(); // Get a character from keyboard

        if (ch == '\n') { // Stop on newline
            break; // Exit loop on newline
        }

        if (ch == '\b') { // Handle backspace
            if (i > 0) {
                i--; // Move back in buffer
                vga::putchar('\b'); // Move cursor back
                vga::putchar(' '); // Erase the character
                vga::putchar('\b'); // Move cursor back again
            }
        } else {
            buffer[i++] = ch; // Add character to buffer
            vga::putchar(ch); // Echo the character to the screen
        }
    }

    buffer[i] = '\0'; // Null-terminate the string
    return i; // Return the number of characters read
}

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
    while(1) __asm__ __volatile__ ("hlt");
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
    // For every keyboard interrupt we must read port 0x60
    //     otherwise we will not get further keystrokes
    uint8_t scancode = inb(0x60);
    key_translate(scancode);

    send_eoi(irq_number);
    return;
}

void __attribute__((noreturn)) divbyzero_handler(stack_frame_t *frame)
{
    (void)frame;
    klog(3, exception_descriptions[frame->int_num]);

    while(1) __asm__ __volatile__ ("hlt");
}

void init_isr_handlers()
{
    for (int index = 0; index < 256; index++)
        isr_dispatch_table[index] = default_exception_handler;

    for (int index = 32; index < 48; index++)
        isr_dispatch_table[index] = default_irq_handler;

    register_isr_handler(0, divbyzero_handler);
    register_isr_handler(33, keyboard_handler);
    register_isr_handler(80, syscall_handler);
}

extern "C" void C_handler(stack_frame_t *frame) {    
    if (frame->int_num >= 256) {
        klog(3, "Invalid interrupt number");
        return;
    }
    
    if (isr_dispatch_table[frame->int_num] == nullptr) {
        klog(3, "No handler registered");
        return;
    }
    isr_dispatch_table[frame->int_num](frame);
    return;
}
