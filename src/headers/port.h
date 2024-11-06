#ifndef PORT_H
#define PORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t value);

#ifdef __cplusplus
}
#endif

#endif