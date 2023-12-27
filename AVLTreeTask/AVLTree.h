#pragma once

#include<stdbool.h>

// AVL tree (key < 100 symbols)
typedef struct AVLTree AVLTree;

// Creating a AVLTree
AVLTree* createAVLTree();

// Adding/change value into a tree
void addValue(AVLTree* const tree, const char* const key, const char* const value);

// Get value by key
char* getValue(const AVLTree* const tree, const char* const key);

// Check containing of key
bool contains(const AVLTree* const tree, const char* const key);

// Deleting value by key
void deleteValue(const AVLTree* const tree, const char* const key);

// Deleting tree
void deleteAVLTree(const AVLTree** const tree);

//Print using instructions
void instructions(void);