#pragma once
#include<stdbool.h>

// Binary search tree (key < 1000 symbols)
typedef struct BinaryTree BinaryTree;

// Creating a BinaryTree
BinaryTree* createBinaryTree();

// Adding/change value into a tree
void addValue(BinaryTree* const tree, const int key, const char* const value);

// Get value by key
char* getValue(const BinaryTree* const tree, int key);

// Check containing of key
bool contains(const BinaryTree* const tree, const int key);

// Deleting value by key
void deleteValue(const BinaryTree* const tree, int key);

// Deleting tree
void deleteBinaryTree(const BinaryTree** const tree);

//Print using instructions
void instructions(void);