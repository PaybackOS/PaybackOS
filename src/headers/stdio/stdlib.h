#ifndef STDLIB_H
#define STDLIB_H 1
#pragma once

#include <stddef.h>

/*
The memory allocation functions
*/

// Reserve memory of a certain size to a pointer
void *malloc(size_t);
// Resize a pointer
void *realloc(void *, size_t);
// Allocates memory for an array of size elements, each of size bytes, and initializes all elements to 0.
void *calloc(size_t, size_t);
// Free the memory of a pointer
void free(void *);

void panic(int error);

#endif