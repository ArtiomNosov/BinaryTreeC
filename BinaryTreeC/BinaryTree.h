#pragma once
struct Node {
	int Data;
	Node* Left, * Right, * Parent;
};
struct BinaryTree {
	Node* Root;
	int Count;
};
BinaryTree* binary_tree_create();
void binary_tree_add(BinaryTree* binaryTree, int data);
void binary_tree_add_node_in_subtree(Node* node, Node* new_node);
void binary_tree_delete(BinaryTree* binaryTree, int data);
int binary_tree_delete_in_subtree(Node* node, int data);
void binary_tree_dump_TLR(BinaryTree* binaryTree);
void binary_tree_dump_LTR(BinaryTree* binaryTree);
void binary_tree_dump_LRT(BinaryTree* binaryTree);
void binary_tree_dump_TLR_in_subtree(Node* node);
void binary_tree_dump_LTR_in_subtree(Node* node);
void binary_tree_dump_LRT_in_subtree(Node* node);
int* binary_tree_to_array_TLR(BinaryTree* binaryTree);
void binary_tree_to_array_TLR_in_subtree(Node * node, int* array);
BinaryTree* binary_tree_bypass_recovery_from_array_TLR(int* array, int lenght);
Node* binary_tree_find(BinaryTree* binaryTree, int data);
Node* binary_tree_find_in_subtree(Node* node, int data);
Node* binary_tree_next_node(Node* node);
Node* binary_tree_prev_node(Node* node);
void binary_tree_minimum_in_subtree(Node* node, Node* min);
void binary_tree_maximum_in_subtree(Node* node, Node* max);
void binary_tree_free(BinaryTree* binaryTree);
void binary_tree_free_nodes_subtree(Node* node);
int binary_tree_get_count_of_nodes(BinaryTree* binaryTree);