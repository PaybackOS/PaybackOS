#include <stddef.h> // for NULL
#include <stdint.h> // for uintptr_t

#define PAGE_SIZE 4096 // Define the page size
#define MEMORY_POOL_START 0x200000 // Starting address for the memory pool (2 MB)
#define MEMORY_POOL_SIZE   (1 * 1024 * 1024) // 1 MB in bytes
#define MAX_PAGES (MEMORY_POOL_SIZE / PAGE_SIZE) // Calculate maximum pages

static uintptr_t *memory_pool = (uintptr_t *)MEMORY_POOL_START; // Pointer to the memory pool
static int pages_used = 0;

// Simple spinlock structure
typedef struct {
    volatile int locked; // Indicates whether the lock is acquired
} Spinlock;

static Spinlock memory_lock = {0}; // Initialize the lock

/** This function locks the memory data structures. 
 *
 * \return 0 if the lock was acquired successfully. Anything else is
 * failure.
 */
extern int liballoc_lock() {
    while (__atomic_test_and_set(&memory_lock.locked, __ATOMIC_ACQUIRE)) {
        // Busy-wait until the lock is acquired
    }
    return 0; // Lock acquired successfully
}

/** This function unlocks what was previously locked by the liballoc_lock
 * function. 
 *
 * \return 0 if the lock was successfully released.
 */
extern int liballoc_unlock() {
    __atomic_clear(&memory_lock.locked, __ATOMIC_RELEASE); // Release the lock
    return 0; // Lock released successfully
}

/** This function allocates pages from a fixed memory pool. 
 *
 * \return NULL if the pages were not allocated.
 * \return A pointer to the allocated memory.
 */
extern void* liballoc_alloc(int num_pages) {
    if (num_pages <= 0 || pages_used + num_pages > MAX_PAGES) {
        return NULL; // Invalid request or not enough memory
    }

    uintptr_t *allocated_memory = memory_pool + (pages_used * PAGE_SIZE / sizeof(uintptr_t)); // Point to the next available memory
    pages_used += num_pages; // Update the number of pages used
    return (void *)allocated_memory; // Return the allocated memory
}

/** This function frees previously allocated memory. 
 *
 * \return 0 if the memory was successfully freed.
 */
extern int liballoc_free(void* ptr, int num_pages) {
    // In this simple model, we do not track freed memory, so just return success.
    // Implementing a more complex memory management system would require a free list or similar.
    if (ptr < (void *)memory_pool || ptr >= (void *)(memory_pool + MEMORY_POOL_SIZE)) {
        return -1; // Pointer out of bounds
    }

    pages_used -= num_pages; // Update the number of pages used
    if (pages_used < 0) {
        pages_used = 0; // Prevent underflow
    }

    return 0; // Success
}
