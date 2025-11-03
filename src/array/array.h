#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef enum { INT } array_type_t;

typedef struct {
    size_t len;
    size_t capacity;
    array_type_t type;
    void* elements;
} array_t;

/**
 * Allocates and initializes a new contiguous dynamic array structure.
 * Sets the default capacity, determines the element size, and allocates the
 * initial block of contiguous memory on the heap.
 */
array_t* alloc_array(array_type_t type);

/**
 * Allocates and initializes a new contiguous dynamic array structure.
 * Sets the default capacity, determines the element size, and allocates the
 * initial block of contiguous memory on the heap.
 */
void free_array(array_t* array);

/**
 * Adds a new element to the end of the dynamic array.
 * If the array is at capacity, it resizes the contiguous memory block to twice
 * its current size using realloc. It then copies the raw bytes of the new
 * element into the next available position in the buffer.
 */
void push_array(array_t* array, const void* element);

/**
 * Iterates through and prints all elements of the dynamic array.
 * It uses pointer arithmetic (with uint8_t*) to calculate the memory address
 * of each element, casts the pointer to the correct type for printing, and
 * manages output formatting (commas and newlines every 10 elements).
 */
void print_array(array_t* array);

#endif
