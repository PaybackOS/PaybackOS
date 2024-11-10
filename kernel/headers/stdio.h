#ifndef STDIO_H
#define STDIO_H

void kprintf(const char *fmt, ...);
void klog(int level, const char* info);
void clear_terminal();

#endif