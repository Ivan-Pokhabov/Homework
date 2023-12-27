#include <stdio.h>

#include "SyntaxTree.h"
#include "Test.h"

int main()
{
	if (!test())
	{
		return -1;
	}
	FILE* file = NULL;
	fopen_s(&file, "input.txt", "r");
	if (file == NULL)
	{
		printf("File not found");
		return 1;
	}
	SyntaxTree* tree = NULL;
	build(&tree, file);
	fclose(file);
	printf("Prefix expression: ");
	printSyntaxTree(tree);
	printf("\nResult: %d", calculateSyntaxTree(tree));
	deleteSyntaxTree(&tree);
}
