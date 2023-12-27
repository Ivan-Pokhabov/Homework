#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "SyntaxTree.h"

struct SyntaxTree
{
    char operation;
    int operand;
    SyntaxTree* leftChild;
    SyntaxTree* rightChild;
};

void build(SyntaxTree** root, FILE* file)
{
    while (true)
    {
        char currentSymbol = getc(file);
        if (currentSymbol == EOF)
        {
            return;
        }
        switch (currentSymbol)
        {
        case ' ':
        case '(':
            continue;
            break;
        case ')':
            return;
        case '+':
        case '*':
        case '/':
        case '-':
            *root = calloc(1, sizeof(SyntaxTree));
            if (*root == NULL)
            {
                return;
            }
            (*root)->operation = currentSymbol;
            build(&(*root)->leftChild, file);
            build(&(*root)->rightChild, file);
            break;
        default:
            *root = calloc(1, sizeof(SyntaxTree));
            if (*root == NULL)
            {
                return;
            }
            ungetc(currentSymbol, file);
            fscanf_s(file, "%d", &(*root)->operand);
            return;
        }
    }
}

int calculateSyntaxTree(const SyntaxTree* const root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftResult = calculateSyntaxTree(root->leftChild);
    int rightResult = calculateSyntaxTree(root->rightChild);
    switch (root->operation)
    {
    case '+':
        return leftResult + rightResult;
    case '-':
        return leftResult - rightResult;
    case '*':
        return leftResult * rightResult;
    case '/':
        return leftResult / rightResult; 
    default:
        return root->operand;
    }
}

void printSyntaxTree(const SyntaxTree* const root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->operation == '\0')
    {
        printf("%d ", root->operand);
    }
    else
    {
        printf("%c ", root->operation);
        printSyntaxTree(root->leftChild);
        printSyntaxTree(root->rightChild);
    }
}

void deleteSyntaxTree(SyntaxTree** root)
{
    if (*root == NULL)
    {
        return;
    }
    deleteSyntaxTree(&(*root)->leftChild);
    deleteSyntaxTree(&(*root)->rightChild);
    free(*root);
    *root = NULL;
}