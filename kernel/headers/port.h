#ifndef PORT_H
#define PORT_H

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void insw(uint16_t port, void *buffer, uint32_t count);
void outsw(uint16_t port, const void *buffer, uint32_t count);
void io_wait(void);

#endif