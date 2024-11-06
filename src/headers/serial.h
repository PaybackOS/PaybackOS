#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int init_serial();
void print_serial(char* msg);

#ifdef __cplusplus
}
#endif

#endif // STDLIB_H
