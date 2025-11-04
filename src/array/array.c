#include "array/array.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

array_t* alloc_array(array_type_t mode, size_t element_size) {
    size_t default_capacity = 10;
    array_t* array = malloc(sizeof(array_t));

    if(array == NULL) {
        fprintf(stderr, "OOM");
        exit(1);
    }

    array->len = 0;
    array->mode = mode;
    array->element_size = element_size;
    array->capacity = default_capacity;

    if(mode == CONTIGUOUS) {
        array->array_data_t.buffer =
            malloc(sizeof(element_size) * default_capacity);
    } else {
        array->array_data_t.pointers = malloc(sizeof(void*) * default_capacity);
    }

    // Same space in memory so we can check either buffer or pointers.
    if(array->array_data_t.buffer == NULL) {
        fprintf(stderr, "OOM");
        free(array);
        exit(1);
    }

    return array;
}

void free_array(array_t* array) {
    if(array->mode == POINTERS) {
        for(size_t index = 0; index < array->len; index++) {
            free(array->array_data_t.pointers[index]);
        }
    } else
        free(array->array_data_t.buffer);

    free(array);
}

void push_array(array_t* array, const void* const element) {
    if(array == NULL || element == NULL) return;

    // Handle capacity reached
    if(array->len == array->capacity) {
        if(array->mode == CONTIGUOUS) {
            size_t new_size = array->element_size * (array->capacity * 2);
            void* new_elements = realloc(array->array_data_t.buffer, new_size);
            if(new_elements == NULL) {
                fprintf(stderr, "OOM");
                free_array(array);
                exit(1);
            }
            array->array_data_t.buffer = new_elements;
        } else {
            size_t new_size = sizeof(void*) * (array->capacity * 2);
            void** new_elements =
                realloc(array->array_data_t.pointers, new_size);
            if(new_elements == NULL) {
                fprintf(stderr, "OOM");
                free_array(array);
                exit(1);
            }
            array->array_data_t.pointers = new_elements;
        }

        array->capacity *= 2;
    }

    if(array->mode == CONTIGUOUS) {
        uint8_t* buffer_offset = (uint8_t*)array->array_data_t.buffer +
                                 (array->len * array->element_size);
        memcpy(buffer_offset, element, array->element_size);
    } else {
        void* new_pointer = malloc(array->element_size);
        if(new_pointer == NULL) {
            fprintf(stderr, "OOM");
            free_array(array);
            exit(1);
        }

        memcpy(new_pointer, element, array->element_size);
        array->array_data_t.pointers[array->len] = new_pointer;
    }

    array->len += 1;
}


void* pop_array(array_t* array) {
    if(array == NULL || array->len == 0) return NULL;

    array->len -= 1;

    if(array->mode == CONTIGUOUS) {
        uint8_t* source_addr = (uint8_t*)array->array_data_t.buffer + (array->len * array->element_size);

        void* buffer = malloc(array->element_size);
        memcpy(buffer, source_addr, array->element_size);

        return buffer;
    } else {
        void* data_ptr = array->array_data_t.pointers[array->len];
        array->array_data_t.pointers[array->len] = NULL;

        return data_ptr;
    }
}
