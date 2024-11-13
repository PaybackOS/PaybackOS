#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

// Allocate memory of a specified size
void* user_malloc(size_t size);

// Free allocated memory at a specified pointer
void user_free(void* ptr);

// Allocate zero-initialized memory (like calloc)
void* user_calloc(size_t num, size_t size);

// Reallocate memory (resize the allocated block)
void* user_realloc(void* ptr, size_t size);

#endif