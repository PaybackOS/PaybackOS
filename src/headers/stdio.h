#ifndef STDIO_H
#define STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

void kprintf(const char *fmt, ...);
void klog(int level, const char* info);
void clear_terminal();

#ifdef __cplusplus
}
#endif

#endif