#include <stdint.h>

void outb(uint16_t port, uint8_t val) {
    __asm__ volatile (
        "outb %b0, %w1"
        :
        : "a"(val), "Nd"(port)
        : "memory"
    );
    /* Note: %b0 is the low byte of %ax, %w1 is the full 16-bit port number. */
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile (
        "inb %w1, %b0"
        : "=a"(ret)
        : "Nd"(port)
        : "memory"
    );
    return ret;
}

void insw(uint16_t port, void *buffer, uint32_t count) {
    __asm__ volatile (
        "rep insw"
        : "+D"(buffer), "+c"(count)
        : "d"(port)
        : "memory"
    );
    /* rep insw: Reads 'count' words from 'port' to buffer. 
     * +D: Updates destination pointer (buffer)
     * +c: Updates counter (count)
     * d: Uses port in dx */
}

void outsw(uint16_t port, const void *buffer, uint32_t count) {
    __asm__ volatile (
        "rep outsw"
        : "+S"(buffer), "+c"(count)
        : "d"(port)
        : "memory"
    );
    /* rep outsw: Writes 'count' words from buffer to 'port'. 
     * +S: Updates source pointer (buffer)
     * +c: Updates counter (count)
     * d: Uses port in dx */
}

void io_wait(void) {
    outb(0x80, 0);
    /* Writing to port 0x80 is a common way to introduce a small delay in x86 I/O operations. */
}
