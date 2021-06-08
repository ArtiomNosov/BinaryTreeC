#include <stdlib.h>
#include "BinaryTree.h"
int main() {
	BinaryTree* bt = binary_tree_create();
	binary_tree_add(bt, 8);
	binary_tree_add(bt, 2);
	binary_tree_add(bt, 1);
	binary_tree_add(bt, 4);
	binary_tree_add(bt, 3);
	binary_tree_add(bt, 5);
	binary_tree_dump_TLR(bt);
	int* array = binary_tree_to_array_TLR(bt);
	int lenght = binary_tree_get_count_of_nodes(bt);
	binary_tree_free(bt);
	bt = binary_tree_bypass_recovery_from_array_TLR(array, lenght);
	binary_tree_dump_TLR(bt);
	binary_tree_free(bt);
	free(array);
	array = NULL;
}