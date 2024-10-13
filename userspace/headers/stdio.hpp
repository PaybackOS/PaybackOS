#ifndef STDIO_H
#define STDIO_H 1
#pragma once

#include <stdint.h>

extern "C" {
    void print(const char* str);
    void putchar(char c);
    void klog(int level, const char* msg);
    void* readisk(uint32_t lba, uint16_t sectors);
}

#endif