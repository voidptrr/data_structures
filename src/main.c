#include "array/array.h"
#include "bst/bst.h"

#include <stdio.h>

typedef struct {
    int x;
    int y;
} point_t;

int main(void) {
    printf("===========BST===========\n");
    node_t* root = alloc_bst_node(30);
    insert_bst_element(&root, 20);
    insert_bst_element(&root, 40);
    insert_bst_element(&root, 50);

    print_inorder_bst(root);
    free_bst(root);

    printf("===========ARRAY CONTIGUOUS===========\n");
    array_t* array = alloc_array(CONTIGUOUS, sizeof(int));
    for(size_t index = 1; index < 50; index++) {
        int value = (int)index;
        push_array(array, &value);
    }

    for(size_t index = 0; index < array->len; index++) {
        int element =
            *(int*)(array->array_data_t.buffer + (index * array->element_size));
        if(index % 10 == 0 && index != 0) printf("\n");
        printf("%d, ", element);
    }

    free_array(array);
    printf("\n");

    printf("===========ARRAY POINTERS===========\n");
    array_t* array_p = alloc_array(POINTERS, sizeof(point_t));
    for(size_t index = 1; index < 3; index++) {
        point_t t = { .x = index - 1, .y = index + 1 };
        push_array(array_p, &t);
    }

    for(size_t index = 0; index < array_p->len; index++) {
        point_t* current_point = array_p->array_data_t.pointers[index];
        printf("point x: %d, y: %d\n", current_point->x, current_point->y);
    }

    free_array(array_p);
    return 0;
}
