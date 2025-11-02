#include "bst/bst.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: improve this by having num_nodes under a tree structure.
#define MAX_STACK_SIZE 100

node_t *alloc_bst_node(int value) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  if (node == NULL)
    return NULL;

  node->val = value;
  node->left = NULL;
  node->right = NULL;

  return node;
}

void free_bst(node_t *root) {
  if (root == NULL)
    return;

  free_bst(root->left);
  free_bst(root->right);

  free(root);
}

void insert_bst_element(node_t **root, int value) {
  if (*root == NULL) {
    *root = alloc_bst_node(value);
    return;
  }

  node_t *current = *root;
  node_t *parent = NULL;

  while (current != NULL) {
    parent = current;

    if (value < current->val)
      current = current->left;
    else if (value > current->val)
      current = current->right;
    else
      return;
  }

  node_t *new_node = alloc_bst_node(value);
  if (new_node == NULL) {
    fprintf(stderr, "Could not allocate memory");
    free_bst(*root);
    exit(1);
  }

  if (value < parent->val)
    parent->left = new_node;
  else
    parent->right = new_node;
}

void print_inorder_bst(node_t *root) {
  if (root == NULL)
    return;

  node_t *stack[MAX_STACK_SIZE];
  int top = -1;

  node_t *current = root;

  while (current != NULL || top != -1) {
    while (current != NULL) {
      if (top < (MAX_STACK_SIZE - 1)) {
        stack[++top] = current;
        current = current->left;
      } else {
        fprintf(stderr, "Too many tree elements");
        return;
      }
    }

    // current here is NULL as we got to the most left node already
    if (top != -1) {
      current = stack[top--];

      printf("node->val = %d\n", current->val);
      current = current->right;
    }
  }
}
