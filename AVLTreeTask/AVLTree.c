#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "AVLTree.h"

#define VALUE_SIZE 100

typedef struct Node
{
    char key[VALUE_SIZE];
    char value[VALUE_SIZE];
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
    size_t height;
} Node;

struct AVLTree
{
    Node* root;
};

static size_t getHeight(const Node* const node)
{
    return (node == NULL) ? 0 : node->height;
}

static int getBalanceFactor(Node* node)
{
    return getHeight(node->rightChild) - getHeight(node->leftChild);
}

static void updateHeight(Node* node)
{
    size_t heightLeft = getHeight(node->leftChild);
    size_t heightRight = getHeight(node->rightChild);
    node->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
}

AVLTree* createAVLTree(void)
{
    return calloc(1, sizeof(AVLTree));
}

static bool isEmpty(const AVLTree* const tree)
{
    return tree->root == NULL;
}

static Node* rotateRight(Node* const root)
{
    Node* pivot = root->leftChild;
    root->leftChild = pivot->rightChild;
    pivot->parent = root->parent;
    if (pivot->rightChild != NULL)
    {
        pivot->rightChild->parent = root;
    }

    pivot->rightChild = root;
    root->parent = pivot;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

static Node* rotateLeft(Node* const root)
{
    Node* pivot = root->rightChild;
    root->rightChild = pivot->leftChild;
    pivot->parent = root->parent;
    if (pivot->leftChild != NULL)
    {
        pivot->leftChild->parent = root;
    }

    pivot->leftChild = root;
    root->parent = pivot;
    updateHeight(root);
    updateHeight(pivot);
    return pivot;
}

static Node* balance(Node* const node)
{
    if (node == NULL)
    {
        return node;
    }
    updateHeight(node);
    if (getBalanceFactor(node) == 2)
    {
        if (getBalanceFactor(node->rightChild) < 0)
        {
            node->rightChild = rotateRight(node->rightChild);
        }
        return rotateLeft(node);
    }
    if (getBalanceFactor(node) == -2)
    {
        if (getBalanceFactor(node->leftChild) > 0)
        {
            node->leftChild = rotateLeft(node->leftChild);
        }
        return rotateRight(node);
    }
    return node;
}

static void insert(Node* const node, const char* const key, const char* const value)
{
    if (strcmp(key, node->key) == 0)
    {
        strcpy_s(node->value, VALUE_SIZE, value);
        return;
    }
    if (strcmp(key, node->key) < 0)
    {
        if (node->leftChild == NULL)
        {
            Node* newNode = calloc(1, sizeof(Node));
            newNode->parent = node;
            ++(newNode->height);
            strcpy_s(newNode->key, VALUE_SIZE, key);
            strcpy_s(newNode->value, VALUE_SIZE, value);
            node->leftChild = newNode;
            return;
        }
        insert(node->leftChild, key, value);
        node->leftChild = balance(node->leftChild);
    }
    if (strcmp(key, node->key) == 1)
    {
        if (node->rightChild == NULL)
        {
            Node* newNode = calloc(1, sizeof(Node));
            newNode->parent = node;
            ++(newNode->height);
            strcpy_s(newNode->key, VALUE_SIZE, key);
            strcpy_s(newNode->value, VALUE_SIZE, value);
            node->rightChild = newNode;
            return;
        }
        insert(node->rightChild, key, value);
        node->rightChild = balance(node->rightChild);
    }
}

void addValue(AVLTree* const tree, const char* const key, const char* const value)
{
    if (tree == NULL)
    {
        return;
    }
    if (isEmpty(tree))
    {
        Node* newNode = calloc(1, sizeof(Node));
        ++(newNode->height);
        strcpy_s(newNode->key, VALUE_SIZE, key);
        strcpy_s(newNode->value, VALUE_SIZE, value);
        tree->root = newNode;
        return;
    }
    insert(tree->root, key, value);
    tree->root = balance(tree->root);
}

static char* get(const Node* const node, const char* const key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (strcmp(key, node->key) == 0)
    {
        return node->value;
    }
    (strcmp(key, node->key) < 0) ? get(node->leftChild, key) : get(node->rightChild, key);
}

char* getValue(const AVLTree* const tree, const char* const key)
{
    return get(tree->root, key);
}

static bool find(const Node* const node, const char* const key)
{
    if (node == NULL)
    {
        return false;
    }
    if (strcmp(key, node->key) == 0)
    {
        return true;
    }
    (strcmp(key, node->key) == -1) ? find(node->leftChild, key) : find(node->rightChild, key);
}

bool contains(const AVLTree* const tree, const char* const key)
{
    return find(tree->root, key);
}

static Node* findNodeClosestToNode(const Node* const node)
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
    return (leftPathLength > rightPathLength) ? rightmostNodeOnTheLeft : leftmostNodeOnTheLeft;
}

static void copyData(Node* const destination, const Node* const source)
{
    strcpy_s(destination->value, VALUE_SIZE, source->value);
    strcpy_s(destination->key, VALUE_SIZE, source->key);
}

static void deleteNode(Node* node, const char* const key)
{
    if (node == NULL)
    {
        return;
    }
    if (strcmp(key, node->key) == 0)
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
    (strcmp(key, node->key) < 0) ? deleteNode(node->leftChild, key) : deleteNode(node->rightChild, key);
    if (node->parent != NULL)
    {
        if (strcmp(key, node->key) < 0)
        {
            node->parent->leftChild = balance(node->parent->leftChild);
            return;
        }
        node->parent->rightChild = balance(node->parent->leftChild);
    }
}

static void deleteRoot(AVLTree* const tree)
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
    tree->root = balance(newRoot);
}

void deleteValue(const AVLTree* const tree, const char* const key)
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

static void deleteChildren(const Node* const node)
{
    if (node == NULL)
    {
        return;
    }
    deleteChildren(node->leftChild);
    deleteChildren(node->rightChild);
    free(node);
}

void deleteAVLTree(const AVLTree** const tree)
{
    deleteChildren((*tree)->root);
    free(*tree);
    *tree = NULL;
}

void instructions(void)
{
    printf("0 - Выйти\n");
    printf("1 - Добавить значение по ключу\n");
    printf("2 - Найти значение по ключу\n");
    printf("3 - Проверить существование ключа\n");
    printf("4 - Удалить ключ и значение\n");
}