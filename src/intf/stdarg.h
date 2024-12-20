#pragma once

typedef char* va_list;

#define _VA_SIZEOF(type) ((sizeof(type) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#define va_start(ap, last) (ap = (va_list)&last + _VA_SIZEOF(last))

#define va_arg(ap, type) \
    (*(type*)((ap += _VA_SIZEOF(type)) - _VA_SIZEOF(type)))

#define va_end(ap) (ap = (va_list)0)