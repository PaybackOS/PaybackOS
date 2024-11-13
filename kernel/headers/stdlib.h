#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

void *kmalloc(size_t);
void *krealloc(void *, size_t);
void *kcalloc(size_t, size_t);
void kfree(void *);

#endif // STDLIB_H
