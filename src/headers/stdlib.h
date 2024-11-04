#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *kmalloc(size_t);
void *krealloc(void *, size_t);
void *kcalloc(size_t, size_t);
void kfree(void *);

#ifdef __cplusplus
}
#endif

#endif // STDLIB_H
