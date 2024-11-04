#ifndef STDARG_H
#define STDARG_H

// A simple type to represent the variable argument list
typedef char* va_list;

// Align the size of each argument to the size of int or the size of the type
#define __va_align(type) (((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

// Macro to initialize the va_list 'ap' to point to the first argument after 'last'
#define va_start(ap, last) (ap = (va_list)&last + __va_align(last))

// Macro to retrieve the next argument in the list. 'type' is the type of the next argument
#define va_arg(ap, type) (*(type*)((ap += __va_align(type)) - __va_align(type)))

// Macro to end the traversal of the arguments
#define va_end(ap) (ap = (va_list)0)

#endif /* STDARG_H */
