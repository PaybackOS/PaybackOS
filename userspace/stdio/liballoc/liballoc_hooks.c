#include <stddef.h> // for NULL
#include <stdint.h> // for uintptr_t

#define PAGE_SIZE 4096 // Define the page size
#define MAX_PAGES 1024 // Define maximum pages for this example

static char memory_pool[PAGE_SIZE * MAX_PAGES];
static int pages_used = 0;

// Simple spinlock structure
typedef struct {
    volatile int locked; // Indicates whether the lock is acquired
} Spinlock;

static Spinlock memory_lock = {0}; // Initialize the lock

/** This function is supposed to lock the memory data structures. 
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

/** This is the hook into the local system which allocates pages. 
 *
 * \return NULL if the pages were not allocated.
 * \return A pointer to the allocated memory.
 */
extern void* liballoc_alloc(int num_pages) {
    if (num_pages <= 0 || pages_used + num_pages > MAX_PAGES) {
        return NULL; // Invalid request or not enough memory
    }

    void* allocated_memory = (void*)(memory_pool + (pages_used * PAGE_SIZE));
    pages_used += num_pages; // Update the number of pages used
    return allocated_memory; // Return the allocated memory
}

/** This frees previously allocated memory. 
 *
 * \return 0 if the memory was successfully freed.
 */
extern int liballoc_free(void* ptr, int num_pages) {
    // Check if the pointer is within the bounds of the memory pool
    if (ptr < (void*)memory_pool || ptr >= (void*)(memory_pool + sizeof(memory_pool))) {
        return -1; // Pointer out of bounds
    }

    pages_used -= num_pages; // Update the number of pages used
    if (pages_used < 0) {
        pages_used = 0; // Prevent underflow
    }

    return 0; // Success
}
