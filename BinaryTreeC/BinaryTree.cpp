#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BinaryTree.h"
#include "AdditionalFunctions.h"
BinaryTree* binary_tree_create() {
	BinaryTree* binaryTree = (BinaryTree*)malloc(sizeof(BinaryTree));
	if (binaryTree == NULL)
		return NULL;
	binaryTree->Root = NULL;
	binaryTree->Count = 0;
	return binaryTree;
}
void binary_tree_add(BinaryTree* binaryTree, int data) {
	if (binaryTree == NULL)
		return;
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL)
		return;
	new_node->Data = data;
	new_node->Parent = NULL;
	new_node->Left = NULL;
	new_node->Right = NULL;
	binaryTree->Count++;
	if (binaryTree->Root == NULL) {
		binaryTree->Root = new_node;
		return;
	}
	binary_tree_add_node_in_subtree(binaryTree->Root, new_node);
}
void binary_tree_add_node_in_subtree(Node* node, Node* new_node) {
	
	if (new_node->Data < node->Data) {
		if (node->Left != NULL) {
			binary_tree_add_node_in_subtree(node->Left, new_node);
			return;
		}
		node->Left = new_node;
		new_node->Parent = node;
	}
	else {
		if (node->Right != NULL) {
			binary_tree_add_node_in_subtree(node->Right, new_node);
			return;
		}
		node->Right = new_node;
		new_node->Parent = node;
	}
}
void binary_tree_delete(BinaryTree* binaryTree, int data) {
	if (binaryTree == NULL) {
		assert(0);
		return;
	}
	if (binaryTree->Root == NULL)
		return;
	if (binary_tree_delete_in_subtree(binaryTree->Root, data) != NULL)
		binaryTree->Count--;
}
int binary_tree_delete_in_subtree(Node* node, int data) {
	Node* delete_node = binary_tree_find_in_subtree(node, data);       
	if (delete_node == NULL)
		return NULL;
	Node* parent_node = delete_node->Parent;                                
	// first if delete node is leaf
	if (delete_node->Left == NULL && delete_node->Right == NULL) {
		if (parent_node->Left == delete_node)
			parent_node->Left = NULL;
		if (parent_node->Right == delete_node)
			parent_node->Right = NULL;
	}
	// second if delete node has a one chield
	else if (delete_node->Left == NULL or delete_node->Right == NULL) {
		if (delete_node->Left == NULL) {
			if (parent_node->Left == delete_node)
				parent_node->Left = delete_node->Right;
			else {
				parent_node->Right = delete_node->Right;
				delete_node->Right->Parent = parent_node;
			}
		}
		else {
			if (parent_node->Left == delete_node)
				parent_node->Left = delete_node->Left;
			else {
				parent_node->Right = delete_node->Left;
				delete_node->Left->Parent = parent_node;
			}
		}
	}
	// third if delete node has two chield
	else  {                                        
		Node* successor = binary_tree_next_node(delete_node);
		delete_node->Data = successor->Data;
		if (successor->Parent->Left == successor) {
			successor->Parent->Left = successor->Right;
			if (successor->Right != NULL)
				successor->Right->Parent = successor->Parent;
		}
		else {
			successor->Parent->Right = successor->Right;
			if (successor->Right != NULL)
				successor->Right->Parent = successor->Parent;
		}
		delete_node = successor;
	}
	free(delete_node);
	delete_node = NULL;
	return 1;
}
void binary_tree_dump_TLR(BinaryTree* binaryTree) {
	if (binaryTree == NULL) {
		assert(0);
		return;
	}
	binary_tree_dump_TLR_in_subtree(binaryTree->Root);
	printf("\n");
}
void binary_tree_dump_LTR(BinaryTree* binaryTree) {
	if (binaryTree == NULL) {
		assert(0);
		return;
	}
	binary_tree_dump_LTR_in_subtree(binaryTree->Root);
	printf("\n");
}
void binary_tree_dump_LRT(BinaryTree* binaryTree) {
	if (binaryTree == NULL) {
		assert(0);
		return;
	}
	binary_tree_dump_LRT_in_subtree(binaryTree->Root);
	printf("\n");
}
void binary_tree_dump_TLR_in_subtree(Node* node) {
	if (node == NULL)
		return;
	printf("%d ", node->Data);
	binary_tree_dump_TLR_in_subtree(node->Left);
	binary_tree_dump_TLR_in_subtree(node->Right);
}
void binary_tree_dump_LTR_in_subtree(Node* node) {
	if (node == NULL)
		return;
	binary_tree_dump_LTR_in_subtree(node->Left);
	printf("%d ", node->Data);
	binary_tree_dump_LTR_in_subtree(node->Right);
}
void binary_tree_dump_LRT_in_subtree(Node* node) {
	if (node == NULL)
		return;
	binary_tree_dump_LRT_in_subtree(node->Left);
	binary_tree_dump_LRT_in_subtree(node->Right);
	printf("%d ", node->Data);
}
int* binary_tree_to_array_TLR(BinaryTree* binaryTree) {
	if (binaryTree == NULL) {
		assert(0);
		return NULL;
	}
	if (binaryTree->Root == NULL) {
		return NULL;
	}
	int* array = (int*)malloc(sizeof(int) * binaryTree->Count);
	if (array == NULL)
		return NULL;
	binary_tree_to_array_TLR_in_subtree(binaryTree->Root, array);
	return array;
}
void binary_tree_to_array_TLR_in_subtree(Node * node, int* array) {
	if (node == NULL)
		return;
	*array = node->Data;
	binary_tree_to_array_TLR_in_subtree(node->Left, ++array);
	binary_tree_to_array_TLR_in_subtree(node->Right, ++array);
}
Node* binary_tree_next_node(Node* node) {
	Node* min = NULL;
	if (node->Right != NULL) {
		binary_tree_maximum_in_subtree(node->Right, min);
		return min;
	}
	min = node->Parent;
	while (min != NULL && node == min->Right) {
		node = min;
		min = min->Parent;
	}
	return min;
}
Node* binary_tree_prev_node(Node* node) {
	Node* max = NULL;
	if (node->Left != NULL) {
		binary_tree_maximum_in_subtree(node->Left, max);
		return max;
	}
	max = node->Parent;
	while (max != NULL && node == max->Left) {
		node = max;
		max = max->Parent;
	}
	return max;
}
void binary_tree_minimum_in_subtree(Node* node, Node* min) {
	if (node == NULL)
		return;
	if (min == NULL) {
		min = node;
	}
	if (node->Left == NULL) {
		min = node;
		return;
	}
	binary_tree_minimum_in_subtree(node->Left, min);
}
void binary_tree_maximum_in_subtree(Node* node, Node* max) {
	if (node == NULL)
		return;
	if (max == NULL) {
		max = node;
	}
	if (max == NULL) {
		max = node;
	}
	if (node->Right == NULL) {
		max = node;
		return;
	}
	binary_tree_maximum_in_subtree(node->Right, max);
}
Node* binary_tree_find(BinaryTree* binaryTree, int data) {
	if (binaryTree == NULL) {
		assert(0);
		return NULL;
	}
	if (binaryTree->Root == NULL) {
		return NULL;
	}
	return binary_tree_find_in_subtree(binaryTree->Root, data);
}
Node* binary_tree_find_in_subtree(Node* node, int data) {
	if (node == NULL || data == node->Data)
		return node;
	if (data < node->Data)
		return binary_tree_find_in_subtree(node->Left, data);
	else
		return binary_tree_find_in_subtree(node->Right, data);
}
BinaryTree* binary_tree_bypass_recovery_from_array_TLR(int* array, int lenght) {
	if (array == NULL || lenght <= 0)
		return NULL;
	BinaryTree* binaryTree = binary_tree_create();
	if (binaryTree == NULL)
		return NULL;
	int start_lenght = lenght;
	binary_tree_add(binaryTree, *array);
	lenght--;
	array++;
	Node* cur = binaryTree->Root;
	while (lenght > 0) {
		do  {
			cur->Left = (Node*)malloc(sizeof(Node));
			cur->Left->Data = *array;
			cur->Left->Parent = cur;
			cur->Left->Left = NULL;
			cur->Left->Right = NULL;
			cur = cur->Left;
			array++;
			lenght--;
		} while (*array < *(array - 1));
		int* buf_ptr = array - 1;
		cur = binary_tree_find(binaryTree, get_max_number_low_then_choice_number_in_array_go_beck(buf_ptr, start_lenght - lenght, *array));
		if (cur == NULL) {
			assert(0);
			return NULL;
		}
		cur->Right = (Node*)malloc(sizeof(Node));
		if (cur->Right == NULL) {
			assert(0);
			return NULL;
		}
		cur->Right->Data = *array;
		cur->Right->Parent = cur;
		cur->Right->Left = NULL;
		cur->Right->Right = NULL;
		cur = cur->Right;
		array++;
		lenght--;
	}
	return binaryTree;
}
void binary_tree_free(BinaryTree* binaryTree) {
	if (binaryTree == NULL) return;
	binary_tree_free_nodes_subtree(binaryTree->Root);
}
void binary_tree_free_nodes_subtree(Node* node) {
	if (node == NULL) return;
	if (node->Left != NULL)
		binary_tree_free_nodes_subtree(node->Left);
	if (node->Right != NULL)
		binary_tree_free_nodes_subtree(node->Right);
	free(node);
	node = NULL;
}
int binary_tree_get_count_of_nodes(BinaryTree* binaryTree) {
	if (binaryTree == NULL) {
		assert(0);
		return NULL;
	}
	return binaryTree->Count;
}