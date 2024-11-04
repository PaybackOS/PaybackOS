#ifndef STDLIB_H
#define STDLIB_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void *malloc(size_t);
void *realloc(void *, size_t);
void *calloc(size_t, size_t);
void free(void *);

#ifdef __cplusplus
}
#endif

#endif