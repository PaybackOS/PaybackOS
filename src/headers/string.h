#ifndef STRING_H
#define STRING_H 1
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memmove(void* dest, const void* src, size_t n);
void memcpy(void *dest, void *src, size_t n);
void strcpy(char *dest, char *src);
int strcmp(const char *s1, const char *s2);
char* strstr(const char* haystack, const char* needle);

#ifdef __cplusplus
}
#endif

#endif