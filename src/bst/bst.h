#ifndef BST_H
#define BST_H

typedef struct node {
  int val;
  struct node *left;
  struct node *right;
} node_t;

node_t *alloc_bst_node(int value);
void free_bst(node_t *root);
void insert_bst_element(node_t **root, int value);
void print_inorder_bst(node_t *root);

#endif
