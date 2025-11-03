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

array_t* alloc_array(array_type_t type);
void free_array(array_t* array);
void push_array(array_t* array, const void* element);
void print_array(array_t* array);

#endif
