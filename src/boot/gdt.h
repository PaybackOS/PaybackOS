#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>

// Forward declare the structs
struct gdt_entry_t;
struct gdt_ptr_t;

// Function prototypes
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void init_gdt();

#endif  // _GDT_H_
