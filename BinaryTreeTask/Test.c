#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "Test.h"
#include "Dictionary.h"

bool test1(void)
{
	BinaryTree* tree = createBinaryTree();
	char value1[7] = "matmeh";
	char value2[6] = "23B10";

	addValue(tree, 1, value1);
	addValue(tree, 10, value1);
	addValue(tree, 17, value2);
	addValue(tree, 35, value1);
	addValue(tree, 14, value2);
	addValue(tree, 15, value2);
	addValue(tree, 10, value2);
	addValue(tree, 7, value1);
	
	bool passed = contains(tree, 1) && !contains(tree, 5) && (strcmp(getValue(tree, 10), value2) == 0);
	deleteValue(tree, 25);
	deleteValue(tree, 10);
	deleteValue(tree, 17);
	deleteValue(tree, 1);
	passed = passed && !contains(tree, 1) && !contains(tree, 217) && contains(tree, 35);
	deleteBinaryTree(&tree);
	return passed;
}

bool test2(void)
{
	BinaryTree* tree = createBinaryTree();
	char value1[7] = "matmeh";

	addValue(tree, 1, value1);
	

	bool passed = contains(tree, 1) && !contains(tree, 5) && (strcmp(getValue(tree, 1), value1) == 0);
	
	deleteValue(tree, 1);
	passed = passed && !contains(tree, 1) && !contains(tree, 217) && !contains(tree, 45);
	deleteBinaryTree(&tree);
	return passed;
}

bool test3(void)
{
	BinaryTree* tree = createBinaryTree();
	char value1[7] = "matmeh";
	char value2[6] = "23B10";

	addValue(tree, 1, value1);
	addValue(tree, 2, value1);
	addValue(tree, 1, value2);

	bool passed = contains(tree, 1) && contains(tree, 2);
	deleteValue(tree, 1);
	passed = passed && !contains(tree, 1) && contains(tree, 2) && (strcmp(getValue(tree, 2), value1) == 0);
	deleteBinaryTree(&tree);
	return passed;
}

bool test(void)
{
	bool passed = true;
	if (!test1())
	{
		printf("Test 1 did not complete\n");
		passed = false;
	}
	if (!test2())
	{
		printf("Test 2 did not complete\n");
		passed = false;
	}
	if (!test3())
	{
		printf("Test 3 did not complete\n");
		passed = false;
	}
	return passed;
}