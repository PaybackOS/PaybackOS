#include <stddef.h>  // for NULL

// Define a page size (assuming 4 KB)
#define PAGE_SIZE 4096

// Simple lock mechanism (global flag)
static int alloc_lock = 0; // 0 means unlocked, 1 means locked

// Structure to simulate page allocation (linked list)
typedef struct AllocBlock {
    void* ptr;                // Pointer to the allocated memory
    int pages;                // The number of pages allocated
    struct AllocBlock* next;  // Pointer to the next block in the list
} AllocBlock;

static AllocBlock* alloc_list = NULL;  // The linked list of all allocated memory blocks

/** 
 * This function locks the memory management structures.
 * It sets the alloc_lock to prevent concurrent access.
 * 
 * \return 0 if the lock was acquired successfully, anything else for failure.
 */
int liballoc_lock() {
    if (alloc_lock) {
        return 1;  // Lock already acquired
    }
    alloc_lock = 1;  // Acquire lock
    return 0;        // Lock acquired successfully
}

/**
 * This function unlocks the memory management structures.
 * It clears the alloc_lock, allowing subsequent allocations.
 * 
 * \return 0 if the lock was successfully released.
 */
int liballoc_unlock() {
    if (!alloc_lock) {
        return 1;  // Lock was not acquired
    }
    alloc_lock = 0;  // Release lock
    return 0;        // Lock released successfully
}

/**
 * This function allocates the required number of pages (each with PAGE_SIZE) 
 * and returns a pointer to the allocated memory.
 * The implementation assumes the memory pool is managed manually.
 * 
 * \param pages The number of pages to allocate.
 * \return NULL if allocation failed; a pointer to the allocated memory otherwise.
 */
void* liballoc_alloc(int pages) {
    if (pages <= 0) {
        return NULL;  // Invalid allocation request
    }

    // Simulate allocating pages starting at an "arbitrary" base address
    // This assumes you have a starting point for available memory. We're using a simple formula.
    void* allocated_memory = (void*)(0x100000 + (pages * PAGE_SIZE));  // Adjusted as per pages requested

    // Create an allocation record
    AllocBlock* new_alloc = (AllocBlock*)0x200000;  // Dummy "memory space" for the allocation tracking (assumed space)
    new_alloc->ptr = allocated_memory;
    new_alloc->pages = pages;
    new_alloc->next = alloc_list;  // Link this allocation with the existing list
    alloc_list = new_alloc;  // Now this block is part of the allocated list

    return allocated_memory;
}

/**
 * This function frees the previously allocated memory.
 * It searches the allocation list, identifies the allocated block,
 * and returns the memory to be "freed."
 * 
 * \param ptr Pointer to the allocated memory to be freed.
 * \param pages The number of pages to free.
 * \return 0 if the memory was successfully freed; non-zero otherwise.
 */
int liballoc_free(void* ptr, int pages) {
    if (!ptr || pages <= 0) {
        return 1;  // Invalid input
    }

    // Lock memory management structure before freeing
    if (liballoc_lock() != 0) {
        return 2;  // Lock acquisition failed
    }

    // Traverse the allocation list to find the matching allocation block
    AllocBlock* prev = NULL;
    AllocBlock* curr = alloc_list;
    while (curr != NULL) {
        // We found the block matching the pointer and number of pages
        if (curr->ptr == ptr && curr->pages == pages) {
            // Mark it as freed by removing it from the list
            if (prev != NULL) {
                prev->next = curr->next;  // Remove current block from the linked list
            } else {
                alloc_list = curr->next;  // The block to free is the first block in the list
            }

            // "Free" the allocated memory (you'd likely be returning this back to the memory pool in a real OS)
            // For now, we'll just consider this freed.

            // Since we are simulating low-level memory, we won't actually free memory in this mock-up.
            // Real OS code would involve memory pool management for actual memory deallocation.

            // Assuming the allocation was successfully freed
            liballoc_unlock();  // Release the lock
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    // No matching block was found for the provided pointer
    liballoc_unlock();  // Release the lock
    return 3;  // No matching allocation was found
}
