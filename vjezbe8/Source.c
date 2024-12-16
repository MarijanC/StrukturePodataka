#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _node;
typedef struct _node* Position;
typedef struct _node {
	int value;
	Position left;
	Position right;
}Node;

Position CreateNode(int value);
int InputValue(Position root, int num);

int main()
{
	Node root = { .value = NULL, .left = NULL, .right = NULL };

	InputValue(&root, 3);
	InputValue(&root, 2);
	InputValue(&root, 5);
	InputValue(&root, 4);
	InputValue(&root, 6);

	printf("%d %d %d %d %d\n", root.value, root.left->value, root.right->value, root.right->left->value, root.right->right->value);

	return 0;
}

Position CreateNode(int value)
{
	Position node = (Position)malloc(sizeof(Node));
	node->value = value;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int InputValue(Position root, int num)
{
	if (root == NULL)
		root = CreateNode(num);
	else if (num < root)
		InputValue(root->left, num);
	else if (num > root)
		InputValue(root->right, num);

	return EXIT_SUCCESS;
}