#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "Test.h"
#include "SyntaxTree.h"

bool test1(void)
{
	bool passed = true;
	FILE* file = NULL;
	fopen_s(&file, "test1.txt", "r");
	if (file == NULL)
	{
		printf("File not found");
		return false;
	}
	char expression[1000];
	fgets(expression, 1000, file);
	fclose(file);
	SyntaxTree* tree = build(expression);
	if (calculate(tree) != 10)
	{
		passed = false;
	}
	deleteSyntaxTree(&tree);
	return passed;
}

bool test2(void)
{
	bool passed = true;
	FILE* file = NULL;
	fopen_s(&file, "test2.txt", "r");
	if (file == NULL)
	{
		printf("File not found");
		return false;
	}
	char expression[1000];
	fgets(expression, 1000, file);
	fclose(file);
	SyntaxTree* tree = build(expression);
	if (calculate(tree) != 3)
	{
		passed = false;
	}
	deleteSyntaxTree(&tree);
	return passed;
}

bool test3(void)
{
	bool passed = true;
	FILE* file = NULL;
	fopen_s(&file, "test3.txt", "r");
	if (file == NULL)
	{
		printf("File not found");
		return false;
	}
	char expression[1000];
	fgets(expression, 1000, file);
	fclose(file);
	SyntaxTree* tree = build(expression);
	if (calculate(tree) != 0)
	{
		passed = false;
	}
	deleteSyntaxTree(&tree);
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