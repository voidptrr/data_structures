#include "array/array.h"
#include "bst/bst.h"

#include <stdio.h>

int main(void) {
    printf("===========BST===========\n");
    node_t* root = alloc_bst_node(30);
    insert_bst_element(&root, 20);
    insert_bst_element(&root, 40);
    insert_bst_element(&root, 50);

    print_inorder_bst(root);
    free_bst(root);

    printf("===========ARRAY===========\n");
    array_t* array = alloc_array(INT);
    for(size_t index = 1; index < 50; index++) {
        int value = (int)index;
        push_array(array, &value);
    }

    print_array(array);
    free_array(array);

    return 0;
}
