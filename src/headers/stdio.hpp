#ifndef STDIO_HPP
#define STDIO_HPP 1
#pragma once

void kprintf(const char *fmt, ...);
void klog(int level, const char* info);
namespace serial {

    int init_serial();
    void putchar(char a);
    void print(const char* string);
    void printf(const char *fmt, ...);
}
#endif