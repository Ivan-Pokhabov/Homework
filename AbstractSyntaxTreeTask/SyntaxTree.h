#pragma once

// Abstract syntax tree struct
typedef struct SyntaxTree SyntaxTree;

// Build syntax treee
SyntaxTree* build(char* string);

// Print tree in infix form
void printSyntaxTree(SyntaxTree* tree);

// Calculating tree
int calculate(SyntaxTree* tree);

// Deleting tree
void deleteSyntaxTree(SyntaxTree** tree);