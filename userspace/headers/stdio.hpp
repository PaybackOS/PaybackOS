#ifndef STDIO_H
#define STDIO_H 1
#pragma once

extern "C" {
    void print(const char* str);
    void putchar(char c);
    void klog(int level, const char* msg);
}

#endif