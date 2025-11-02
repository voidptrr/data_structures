#include "bst/bst.h"

int main(void) {
  node_t *root = alloc_bst_node(30);
  insert_bst_element(&root, 20);
  insert_bst_element(&root, 40);
  insert_bst_element(&root, 50);

  print_inorder_bst(root);
  free_bst(root);
  return 0;
}
