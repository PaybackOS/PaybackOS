#ifndef STRING_H
#define STRING_H 1
#pragma once

char *strstr(const char *haystack, const char *needle);
void* memcpy(void* dest, const void* src, size_t size);
int memcmp(const void* src, const void* dest, size_t size);
size_t strlen(const char* str);
void strcpy(void* dest, char* data);

#endif