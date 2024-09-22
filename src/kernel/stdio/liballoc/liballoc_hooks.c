/*
This code WAS NOT! taken from liballoc it was written for liballoc to use freely
*/
#include <liballoc.h>

// Global variables for memory allocation
static void* heap_start = NULL;
static void* heap_end = NULL;
static size_t heap_size = 0;
// Simple lock mechanism
static volatile int lock = 0;

// Implementation of liballoc_lock
int liballoc_lock() {
    if (lock == 0) {
        lock = 1;
        return 0;
    }
    return 1;
}

// Implementation of liballoc_unlock
int liballoc_unlock() {
    if (lock == 1) {
        lock = 0;
        return 0;
    }
    return 1;
}

// Implementation of liballoc_alloc
void* liballoc_alloc(int pages) {
    if (lock != 0 || heap_end - heap_start < pages * sizeof(struct boundary_tag)) {
        return NULL;
    }
    
    void* result = heap_start;
    heap_start += sizeof(struct boundary_tag) * pages;
    heap_size -= sizeof(struct boundary_tag) * pages;
    
    struct boundary_tag* tag = result;
    tag->magic = 0x12345678; // Magic number
    tag->size = sizeof(struct boundary_tag);
    tag->real_size = sizeof(struct boundary_tag);
    tag->index = 0;
    tag->split_left = NULL;
    tag->split_right = NULL;
    tag->next = NULL;
    tag->prev = NULL;
    
    return result;
}

// Implementation of liballoc_free
int liballoc_free(void* ptr, int pages) {
    if (lock != 0) {
        return 1;
    }
    
    struct boundary_tag* tag = ptr;
    if (tag->magic != 0x12345678) {
        return 1;
    }
    
    heap_start -= sizeof(struct boundary_tag) * pages;
    heap_size += sizeof(struct boundary_tag) * pages;
    
    return 0;
}
