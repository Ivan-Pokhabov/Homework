#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Dictionary.h"

#define VALUE_SIZE 1000

typedef struct Node
{
    int key;
    char value[VALUE_SIZE];
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct BinaryTree
{
    Node* root;
};

BinaryTree* createBinaryTree(void)
{
    return calloc(1, sizeof(BinaryTree));
}

bool isEmpty(const BinaryTree* const tree)
{
    return tree->root == NULL;
}

void insert(Node* const node, const int key, const char* const value)
{
    if (key == node->key)
    {
        strcpy_s(node->value, VALUE_SIZE, value);
        return;
    }
    if (key < node->key)
    {
        if (node->leftChild == NULL)
        {
            Node* newNode = calloc(1, sizeof(Node));
            newNode->parent = node;
            newNode->key = key;
            strcpy_s(newNode->value, VALUE_SIZE, value);
            node->leftChild = newNode;
            return;
        }
        insert(node->leftChild, key, value);
    }
    if (key > node->key)
    {
        if (node->rightChild == NULL)
        {
            Node* newNode = calloc(1, sizeof(Node));
            newNode->parent = node;
            newNode->key = key;
            strcpy_s(newNode->value, VALUE_SIZE, value);
            node->rightChild = newNode;
            return;
        }
        insert(node->rightChild, key, value);
    }
}

void addValue(BinaryTree* const tree, const int key, const char* const value)
{
    if (tree == NULL)
    {
        return;
    }
    if (isEmpty(tree))
    {
        Node* newNode = calloc(1, sizeof(Node));
        newNode->key = key;
        strcpy_s(newNode->value, VALUE_SIZE, value);
        tree->root = newNode;
        return;
    }
    insert(tree->root, key, value);
}

char* get(const Node* const node, const int key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (key == node->key)
    {
        return node->value;
    }
    if (key < node->key)
    {
        get(node->leftChild, key);
    }
    else
    {
        get(node->rightChild, key);
    }
}

char* getValue(const BinaryTree* const tree, const int key)
{
    return get(tree->root, key);
}

bool find(const Node* const node, const int key)
{
    if (node == NULL)
    {
        return false;
    }
    if (key == node->key)
    {
        return true;
    }
    if (key < node->key)
    {
        find(node->leftChild, key);
    }
    else
    {
        find(node->rightChild, key);
    }
}

bool contains(const BinaryTree* const tree, const int key)
{
    return find(tree->root, key);
}

Node* findNodeClosestToNode(const Node* const node)
{
    Node* rightmostNodeOnTheLeft = node->leftChild;
    int leftPathLength = 1;
    while (rightmostNodeOnTheLeft->rightChild != NULL)
    {
        rightmostNodeOnTheLeft = rightmostNodeOnTheLeft->rightChild;
        leftPathLength++;
    }
    Node* leftmostNodeOnTheLeft = node->rightChild;
    int rightPathLength = 1;
    while (leftmostNodeOnTheLeft->leftChild != NULL)
    {
        leftmostNodeOnTheLeft = leftmostNodeOnTheLeft->leftChild;
        rightPathLength++;
    }
    if (leftPathLength > rightPathLength) 
    {
        return rightmostNodeOnTheLeft;
    }
    return leftmostNodeOnTheLeft;
}

void copyData(Node* const destination, const Node* const source)
{
    strcpy_s(destination->value, VALUE_SIZE, source->value);
    destination->key = source->key;
}

void deleteNode(const Node* const node, const int key)
{
    if (node == NULL)
    {
        return;
    }
    if (key == node->key)
    {
        if (node->rightChild != NULL && node->leftChild != NULL)
        {
            Node* helpNode = findNodeClosestToNode(node);
            copyData(node, helpNode);
            deleteNode(helpNode, helpNode->key);
            return;
        }
        if (node->rightChild == NULL)
        {
            if (node->leftChild != NULL)
            {
                node->leftChild->parent = node->parent;
            }
            if (key < node->parent->key)
            {
                node->parent->leftChild = node->leftChild;
            }  
            else
            {
                node->parent->rightChild = node->leftChild;
            }
        }
        else
        {
            if (node->rightChild != NULL)
            {
                node->rightChild->parent = node->parent;
            }
            if (key < node->parent->key)
            {
                node->parent->leftChild = node->rightChild;
            }
            else
            {
                node->parent->rightChild = node->rightChild;
            }
        }
        free(node);
        return;
    }
    if (key < node->key)
    {
        deleteNode(node->leftChild, key);
    }
    else
    {
        deleteNode(node->rightChild, key);
    }
}

void deleteRoot(BinaryTree* const tree)
{
    if (tree->root->rightChild != NULL && tree->root->leftChild != NULL)
    {
        Node* helpNode = findNodeClosestToNode(tree->root);
        copyData(tree->root, helpNode);
        deleteNode(helpNode, helpNode->key);
        return;
    }
    Node* newRoot = NULL;
    if (tree->root->rightChild == NULL)
    {
        newRoot = tree->root->leftChild;
    }
    else
    {
        newRoot = tree->root->rightChild;
    }
    if (newRoot != NULL)
    {
        newRoot->parent = NULL;
    }
    free(tree->root);
    tree->root = newRoot;
}

void deleteValue(const BinaryTree* const tree, const int key)
{
    if (tree == NULL)
    {
        return;
    }
    if (isEmpty(tree))
    {
        return;
    }
    if (tree->root->key == key)
    {
        deleteRoot(tree);
        return;
    }
    deleteNode(tree->root, key);
}

void deleteChildren(const Node* const node)
{
    if (node == NULL)
    {
        return;
    }
    deleteChildren(node->leftChild);
    deleteChildren(node->rightChild);
    free(node);
}

void deleteBinaryTree(const BinaryTree** const tree)
{
    deleteChildren((*tree)->root);
    free(*tree);
    *tree = NULL;
}

void instructions(void)
{
    printf("0 - Âûéòè\n");
    printf("1 - Äîáàâèòü çíà÷åíèå ïî êëþ÷ó\n");
    printf("2 - Íàéòè çíà÷åíèå ïî êëþ÷ó\n");
    printf("3 - Ïðîâåðèòü ñóùåñòâîâàíèå êëþ÷à\n");
    printf("4 - Óäàëèòü êëþ÷ è çíà÷åíèå\n");
}
