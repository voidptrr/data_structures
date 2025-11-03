#include "array/array.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Determines the size in bytes of an array element based on its type.
 */
size_t get_element_size(array_type_t type) {
    switch(type) {
        case INT:
            return sizeof(int);
            break;
        default:
            fprintf(stderr, "Data type not handled");
            exit(1);
            break;
    }
}

array_t* alloc_array(array_type_t type) {
    size_t default_capacity = 10;
    array_t* array = malloc(sizeof(array_t));

    if(array == NULL) {
        fprintf(stderr, "OOM");
        exit(1);
    }

    size_t type_size = get_element_size(type);

    array->len = 0;
    array->type = type;
    array->capacity = default_capacity;
    array->elements = malloc(sizeof(type_size) * default_capacity);

    if(array->elements == NULL) {
        fprintf(stderr, "OOM");
        free(array);
        exit(1);
    }

    return array;
}


void free_array(array_t* array) {
    free(array->elements);
    free(array);
}

void push_array(array_t* array, const void* element) {
    if(array == NULL || element == NULL) return;

    size_t type_size = get_element_size(array->type);

    // Handle capacity reached
    if(array->len == array->capacity) {
        size_t new_size = type_size * array->capacity * 2;
        void* new_elements = realloc(array->elements, new_size);

        if(new_elements == NULL) {
            fprintf(stderr, "OOM");
            free_array(array);
            exit(1);
        }

        array->elements = new_elements;
        array->capacity *= 2;
    }

    uint8_t* buffer = (uint8_t*)array->elements + (array->len * type_size);
    memcpy(buffer, element, type_size);

    array->len += 1;
}


/**
 * Prints the value of a single element based on its type.
 * This function handles the type casting and printing for a single element 
 * retrieved from the generic contiguous array buffer. It does not handle 
 * formatting like commas or newlines.
 */
void print_single_element(const void* element, array_type_t type) {
    switch(type) {
        case INT:
            printf("%d", *(int*)element);
            break;
        default:
            fprintf(stderr, "Data type not handled");
            exit(1);
    }
}


void print_array(array_t* array) {
    if(array == NULL) return;

    size_t type_size = get_element_size(array->type);
    uint8_t* buffer_start = (uint8_t*)array->elements;

    for(size_t index = 0; index < array->len; index++) {
        uint8_t* current = buffer_start + (index * type_size);

        const int index_cast = (int)index;

        print_single_element(current, array->type);
        if((index_cast + 1) % 10 != 0 && index != array->len - 1) printf(",");
        if((index_cast + 1) % 10 == 0) printf("\n");
        if(index == array->len - 1) printf("\n");
    }
}
