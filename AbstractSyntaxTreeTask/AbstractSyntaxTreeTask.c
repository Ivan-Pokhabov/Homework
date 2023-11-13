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
	char expression[1000];
	fgets(expression, 1000, file);
	fclose(file);
	SyntaxTree* tree = build(expression);
	printf("Prefix expression: ");
	printSyntaxTree(tree);
	printf("\nResult: %d", calculate(tree));
	deleteSyntaxTree(&tree);
}
