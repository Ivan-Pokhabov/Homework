#pragma once
#include <stdlib.h>
#include <stdbool.h>

// Struct of priority queue
typedef struct PriorityQueue PriorityQueue;

// Struct of error codes 
typedef enum ErrorCode
{
    ok = 0,
    nullptr = -2,
    memoryError = -3,
    emptyPriorityQueue = -1
} ErrorCode;

// Function of creating pointer to priority queue
PriorityQueue* createPriorityQueue(void);

// Function of adding new element to queue
int enqueue(PriorityQueue* const priorityQueue, const int key, const int value);

// Function of extract minimum from queue
int dequeue(PriorityQueue* const priorityQueue);

// Function of deleteing queue and free memory
void deletePriorityQueue(PriorityQueue** priorityQueue);
