#include <stddef.h>
#include <stdint.h>

typedef void (*constructor)();
extern "C" constructor start_ctors[];
extern "C" constructor end_ctors[];

// Function to iterate through all global constructors and
// call them. This must be done befor calling _init
extern "C" void call_constructors()
{
    size_t n = ((uintptr_t)end_ctors - (uintptr_t)start_ctors)/(sizeof(constructor));
    for (constructor *ctor = start_ctors; ctor < start_ctors + n; ctor++)
        (*ctor)();
}