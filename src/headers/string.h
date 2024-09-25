#ifndef STRING_H
#define STRING_H 1
#pragma once

#include <stddef.h>

void* memmove(void* dest, const void* src, size_t n);
void memcpy(void *dest, void *src, size_t n);
void strcpy(char *dest, char *src);

#endif