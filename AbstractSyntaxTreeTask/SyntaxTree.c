#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "SyntaxTree.h"

typedef struct Node
{
	char operation;
	int operand;
	struct Node* leftChild;
	struct Node* rightChild;
} Node;

struct SyntaxTree
{
	Node* root;
};

SyntaxTree* createSyntaxTree()
{
	return calloc(1, sizeof(SyntaxTree));
}

bool isEmpty(SyntaxTree* tree)
{
	return tree->root == NULL;
}

bool isLeaf(Node* node)
{
	return node->leftChild == NULL && node->rightChild == NULL;
}

bool isOperation(char symbol)
{
	return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int getNumber(char* expression, int* position)
{
	int number = 0;
	while (expression[*position] >= '0' && expression[*position] <= '9')
	{
		number = number * 10 + (expression[*position] - '0');
		++(*position);
	}
	return number;
}

Node* newNode(char* expression, int* position)
{
	++(*position);
	while (expression[*position] == ' ' || expression[*position] == '(' || expression[*position] == ')')
	{
		++(*position);
	}
	Node* node = calloc(1, sizeof(Node));
	if (isOperation(expression[*position]))
	{
		node->operation = expression[*position];
		node->leftChild = newNode(expression, position);
		node->rightChild = newNode(expression, position);
	}
	else
	{
		node->operand = getNumber(expression, position);
	}
	return node;
}

SyntaxTree* build(char* expression)
{
	int position = 0;
	SyntaxTree* tree = createSyntaxTree();
	tree->root = newNode(expression, &position);
	return tree;
}

void printNode(Node* node)
{
	if (isLeaf(node))
	{
		printf("%d ", node->operand);
		return;
	}
	printf("%c ", node->operation);
	printNode(node->leftChild);
	printNode(node->rightChild);
}

void printSyntaxTree(SyntaxTree* tree)
{
	if (isEmpty(tree))
	{
		return;
	}
	printNode(tree->root);
}

int calculateSubtree(Node* node)
{
	if (isLeaf(node))
	{
		return node->operand;
	}
	const int operand1 = calculateSubtree(node->leftChild);
	const int operand2 = calculateSubtree(node->rightChild);
	const char operation = node->operation;
	if (operation == '+')
	{
		return operand1 + operand2;
	}
	if (operation == '-')
	{
		return operand1 - operand2;
	}
	if (operation == '*')
	{
		return operand1 * operand2;
	}
	return operand1 / operand2;
}

int calculate(SyntaxTree* tree)
{
	return calculateSubtree(tree->root);
}

void deleteChildren(Node* node)
{
	if (node == NULL)
	{
		return;
	}
	deleteChildren(node->leftChild);
	deleteChildren(node->rightChild);
	free(node);
}

void deleteSyntaxTree(SyntaxTree** tree)
{
	deleteChildren((*tree)->root);
	free(*tree);
	*tree = NULL;
}