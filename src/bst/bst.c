#include "bst/bst.h"

#include "array/array.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

node_t* alloc_bst_node(int value) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if(node == NULL) return NULL;

    node->val = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void free_bst(node_t* root) {
    if(root == NULL) return;

    free_bst(root->left);
    free_bst(root->right);

    free(root);
}

void insert_bst_element(node_t** root, int value) {
    if(*root == NULL) {
        *root = alloc_bst_node(value);
        return;
    }

    node_t* current = *root;
    node_t* parent = NULL;

    while(current != NULL) {
        parent = current;

        if(value < current->val)
            current = current->left;
        else if(value > current->val)
            current = current->right;
        else
            return;
    }

    node_t* new_node = alloc_bst_node(value);
    if(new_node == NULL) {
        fprintf(stderr, "Could not allocate memory");
        free_bst(*root);
        exit(1);
    }

    if(value < parent->val)
        parent->left = new_node;
    else
        parent->right = new_node;
}

void print_inorder_bst(node_t* root) {
    if(root == NULL) return;

    array_t* node_stack = alloc_array(CONTIGUOUS, sizeof(node_t*));
    node_t* current = root;

    while(current != NULL || node_stack->len != 0) {
        while(current != NULL) {
            push_array(node_stack, &current);
            current = current->left;
        }

        // current here is NULL as we got to the most left node already
        if(node_stack->len != 0) {
            node_t** last_element_ptr = pop_array(node_stack);
            node_t* last_element = *last_element_ptr;
            free(last_element_ptr);

            printf("node->val = %d\n", last_element->val);
            current = last_element->right;
        }
    }

    free(node_stack);
}

node_t* search_bst(node_t* root, int value) {
    array_t* node_stack = alloc_array(CONTIGUOUS, sizeof(node_t*));
    push_array(node_stack, &root);

    while(node_stack->len != 0) {
        node_t** last_element = pop_array(node_stack);
        node_t* element = *last_element;

        if(element->val == value) return element;
        if(value > element->val && element->right != NULL)
            push_array(node_stack, &element->right);

        if(value < element->val && element->left != NULL)
            push_array(node_stack, &element->right);
    }

    free(node_stack);
    return NULL;
}
