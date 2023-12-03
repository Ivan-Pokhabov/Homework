#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct BinaryHeap BinaryHeap;

typedef enum ErrorCode
{
    ok,
    nullptr,
    memoryError,
    emptyHeap
} ErrorCode;

BinaryHeap* createHeap(void);

int add(BinaryHeap* const heap, const int key, const int value);

int pop(BinaryHeap* const heap, int* const key, int* const value);

int build(BinaryHeap* const heap, const int const keys[], const int const values[], const size_t size);

void deleteHeap(BinaryHeap** heap);

bool isEmpty(BinaryHeap* heap);