#ifndef STDIO_HPP
#define STDIO_HPP 1
#pragma once

void printf(const char *fmt, ...);
void klog(int level, const char* info);
char getch();

#endif