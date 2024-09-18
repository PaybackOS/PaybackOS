#ifndef STDARG_H
#define STDARG_H

/* Define a type for variable argument list */
typedef char *va_list;

/* Define the macro to initialize a variable argument list */
#define va_start(ap, param) (ap = (va_list)&param + sizeof(param))

/* Define the macro to retrieve the next argument in the list */
#define va_arg(ap, type) (*(type *)((ap += sizeof(type)) - sizeof(type)))

/* Define the macro to clean up after using a variable argument list */
#define va_end(ap) ((void)0)

#endif
