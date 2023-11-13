#pragma once

// Abstract syntax tree struct
typedef struct SyntaxTree SyntaxTree;

// Build syntax treee
SyntaxTree* build(const char* const expression);

// Print tree in infix form
void printSyntaxTree(const SyntaxTree* const tree);

// Calculating tree
int calculate(const SyntaxTree* const tree);

// Deleting tree
void deleteSyntaxTree(SyntaxTree** tree);