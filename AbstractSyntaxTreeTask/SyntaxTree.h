#pragma once

// Abstract syntax tree struct
typedef struct SyntaxTree SyntaxTree;

// Build syntax tree
void build(SyntaxTree** root, FILE* file);

// Print tree in infix form
void printSyntaxTree(const SyntaxTree* const tree);

// Calculating tree
int calculateSyntaxTree(const SyntaxTree* const tree);

// Deleting tree
void deleteSyntaxTree(SyntaxTree** tree);