#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "Test.h"
#include "AVLtree.h"

static bool test1(void)
{
	AVLTree* tree = createAVLTree();
	char value1[7] = "matmeh";
	char value2[6] = "23B10";

	addValue(tree, "1", value1);
	addValue(tree, "10", value1);
	addValue(tree, "17", value2);
	addValue(tree, "35", value1);
	addValue(tree, "14", value2);
	addValue(tree, "15", value2);
	addValue(tree, "10", value2);
	addValue(tree, "7", value1);

	bool passed = contains(tree, "1") && !contains(tree, "5") && (strcmp(getValue(tree, "10"), value2) == 0);
	
	deleteValue(tree, "25"); 
	deleteValue(tree, "10");
	deleteValue(tree, "17");
	deleteValue(tree, "1");
	
	passed = passed && !contains(tree, "1") && !contains(tree, "217") && contains(tree, "35");
	deleteAVLTree(&tree);
	return passed;
}

static bool test2(void)
{
	AVLTree* tree = createAVLTree();
	char value1[7] = "matmeh";

	addValue(tree, "1", value1);

	bool passed = contains(tree, "1") && !contains(tree, "lol") && (strcmp(getValue(tree, "1"), value1) == 0);

	deleteValue(tree, "1");
	passed = passed && !contains(tree, "1") && !contains(tree, "kek") && !contains(tree, "45");
	deleteAVLTree(&tree);
	return passed;
}

static bool test3(void)
{
	AVLTree* tree = createAVLTree();
	char value1[7] = "matmeh";
	char value2[6] = "23B10";

	addValue(tree, "aba", value1);
	addValue(tree, "ba", value1);
	addValue(tree, "aba", value2);

	bool passed = contains(tree, "aba") && contains(tree, "ba");
	deleteValue(tree, "aba");
	passed = passed && !contains(tree, "aba") && contains(tree, "ba") && (strcmp(getValue(tree, "ba"), value1) == 0);
	deleteAVLTree(&tree);
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