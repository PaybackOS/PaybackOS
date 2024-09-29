#ifndef STDLIB_HPP
#define STDLIB_HPP 1
#pragma once

#include <stddef.h>  // for size_t

void* malloc(size_t size);
void free(void* ptr);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t size);

#endif