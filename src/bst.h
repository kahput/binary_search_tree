#pragma once

#include <stdint.h>

typedef struct _bst BST;

BST* bst_init();
void bst_add(BST* tree, uint32_t value);

void bst_print(BST* tree);

#define BST_IMPLEMENT
#ifdef BST_IMPLEMENT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void* resize_array(void* data, uint32_t new_capacity, size_t element_size) {
	void* tmp = realloc(data, new_capacity * element_size);
	if (!tmp) {
		printf("ERROR: Failed to realloc\n");
		exit(1);
	}

	return tmp;
}

typedef struct _node {
	uint32_t value, depth;
	struct _node *left, *right;
} Node;

struct _bst {
	Node* root;
	uint32_t max_depth, count;
};

BST* bst_init() {
	BST* tree = malloc(sizeof(BST));

	tree->root = NULL;
	tree->max_depth = 0;
	return tree;
}

static inline uint32_t _bst_add_node(Node* node, Node* new_node, uint32_t depth) {
	if (node->value > new_node->value) {
		if (node->left)
			depth = _bst_add_node(node->left, new_node, depth + 1);
		else {
			new_node->depth = depth;
			node->left = new_node;
		}
	} else if (node->value < new_node->value) {
		if (node->right)
			depth = _bst_add_node(node->right, new_node, depth + 1);
		else {
			new_node->depth = depth;
			node->right = new_node;
		}
	}

	return depth;
}

void bst_add(BST* tree, uint32_t value) {
	if (!tree) {
		printf("ERROR: Tree is NULL\n");
		exit(1);
	}

	Node* new_node = malloc(sizeof(Node));
	new_node->value = value;
	new_node->left = new_node->right = NULL;
	new_node->depth = 0;

	if (tree->root == NULL) {
		tree->root = new_node;
		return;
	}

	uint32_t depth = _bst_add_node(tree->root, new_node, 1);
	tree->max_depth = depth > tree->max_depth ? depth : tree->max_depth;
	tree->count++;
}

void bst_print(BST* tree) {
	if (!tree || !tree->root)
		return;
	printf("MaxDepth: %d\n", tree->max_depth);

	Node* queue[tree->count + 1];
	uint32_t offsets[tree->count + 1];
	uint32_t current_offset = 0;
	for (int i = 0; i < tree->count; i++)
		offsets[i] = 0;
	uint32_t front = 0, rear = 0;
	offsets[rear] = 0;
	queue[rear++] = tree->root;
	Node* current = NULL;
	uint32_t current_depth = tree->max_depth;
	printf("%*s", (current_depth + 1) * 2, "");
	while (front < rear) {
		uint32_t offset = offsets[front];
		current_offset = offset;
		current = queue[front++];
		if ((tree->max_depth - current->depth) < current_depth) {
			current_depth = (tree->max_depth - current->depth);
			printf("\n%*s", (current_depth + 1) * 2, "");
			current_offset = 0;
		}

		printf("%*s%2d", offset, "", current->value);
		if (current->left) {
			offsets[rear] = offset;
			queue[rear++] = current->left;
		}

		if (current->right) {
			offsets[rear] += 2;
			queue[rear++] = current->right;
		}
	}

	printf("\n");
}

#endif
