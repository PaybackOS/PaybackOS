#include <stddef.h>
#include <stdint.h>

static volatile uint8_t spinlock = 0;
#define PAGE_SIZE 4096 // Define the size of a page
#define MAX_PAGES 1024 // Define maximum number of pages

static uint8_t memory_pool[MAX_PAGES * PAGE_SIZE]; // Memory pool
static uint8_t page_map[MAX_PAGES]; // Bitmap for tracking free pages

extern "C" int liballoc_lock() {
    while (__sync_lock_test_and_set(&spinlock, 1)) {
        // Busy-wait (spin) until the lock is acquired
    }
    return 0; // Lock acquired successfully
}

extern "C" int liballoc_unlock() {
    __sync_lock_release(&spinlock);
    return 0; // Lock released successfully
}

extern "C" void* liballoc_alloc(int pages) {
    if (pages <= 0 || pages > MAX_PAGES) {
        return NULL; // Invalid request
    }

    // Find a contiguous block of free pages
    for (int i = 0; i < MAX_PAGES; i++) {
        if (page_map[i] == 0) { // Found a free page
            // Check if we can allocate the requested number of pages
            int j;
            for (j = 0; j < pages; j++) {
                if (i + j >= MAX_PAGES || page_map[i + j] != 0) {
                    break; // Not enough contiguous pages
                }
            }
            if (j == pages) { // Found enough free pages
                // Mark pages as allocated
                for (int k = 0; k < pages; k++) {
                    page_map[i + k] = 1; // Mark page as used
                }
                return &memory_pool[i * PAGE_SIZE]; // Return pointer to allocated memory
            }
        }
    }
    return NULL; // Not enough memory
}

extern "C" int liballoc_free(void* ptr, int pages) {
    if (ptr == NULL || pages <= 0) {
        return -1; // Invalid free request
    }

    uintptr_t offset = (uintptr_t)ptr - (uintptr_t)memory_pool; // Calculate offset
    if (offset % PAGE_SIZE != 0) {
        return -1; // Pointer not aligned to page size
    }

    int page_index = offset / PAGE_SIZE; // Find the starting page index
    if (page_index + pages > MAX_PAGES) {
        return -1; // Out of bounds
    }

    // Free the pages
    for (int i = 0; i < pages; i++) {
        if (page_map[page_index + i] == 0) {
            return -1; // Trying to free an already freed page
        }
        page_map[page_index + i] = 0; // Mark page as free
    }

    return 0; // Memory freed successfully
}