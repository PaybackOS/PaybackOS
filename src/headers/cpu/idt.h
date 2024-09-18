#ifndef IDT_H
#define IDT_H 1
#pragma once

#include <stdint.h>

void idt_set_entry(int num, void (*handler)(void), uint16_t selector, uint8_t type_attr);

// Function to initialize the IDT
void init_idt();

#endif