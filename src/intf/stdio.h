#pragma once

#define DEBUG 0
#define INFO 1
#define WARNING 2
#define ERROR 3

void printf(const char* format, ...);
void putchar(char character);
void log(int level, const char* format, ...);