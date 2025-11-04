#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef enum { CONTIGUOUS, POINTERS } array_type_t;

typedef struct {
    size_t len;
    size_t capacity;
    size_t element_size;
    array_type_t mode;
    union {
        void* buffer;
        void** pointers;
    } array_data_t;
} array_t;

/**
 * Allocates and initializes a new generic dynamic array structure.
 * This function sets the storage mode (CONTIGUOUS or POINTERS) and allocates
 * the initial contiguous memory block (either for raw data or for an array of
 * pointers).
 */
array_t* alloc_array(array_type_t mode, size_t element_size);

/**
 * Frees all memory associated with the dynamic array, handling both storage
 * modes. If the mode is POINTERS, this function first loops through and frees
 * the memory block for each stored element before freeing the array of pointers
 * itself. For CONTIGUOUS mode, it just frees the single data buffer.
 */
void free_array(array_t* array);

/**
 * Adds a new element to the end of the dynamic array, managing storage based on
 * the mode. Handles resizing if capacity is reached. For CONTIGUOUS mode, it
 * copies raw data bytes. For POINTERS mode, it allocates new memory on the
 * heap, copies the data into it, and stores the pointer.
 */
void push_array(array_t* array, const void* const element);


void* pop_array(array_t* array);

#endif
