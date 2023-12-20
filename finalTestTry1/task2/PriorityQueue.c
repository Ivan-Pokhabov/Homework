#include <stdlib.h>
#include <stdbool.h>

#include "PriorityQueue.h"

struct PriorityQueue
{
    int* keys;
    int* values;
    size_t size;
    size_t elementsNumber;
};

PriorityQueue* createPriorityQueue(void)
{
    return calloc(1, sizeof(PriorityQueue));
}

static int siftUp(const PriorityQueue* const priorityQueue, size_t index)
{
    if (priorityQueue == NULL || priorityQueue->keys == NULL)
    {
        return nullptr;
    }
    while (index > 1 && priorityQueue->keys[index] < priorityQueue->keys[index / 2])
    {
        int temp = priorityQueue->keys[index];
        priorityQueue->keys[index] = priorityQueue->keys[index / 2];
        priorityQueue->keys[index / 2] = temp;
        temp = priorityQueue->values[index];
        priorityQueue->values[index] = priorityQueue->values[index / 2];
        priorityQueue->values[index / 2] = temp;
        index /= 2;
    }
    return ok;
}

static int siftDown(const PriorityQueue* const priorityQueue, size_t index)
{
    if (priorityQueue == NULL || priorityQueue->keys == NULL)
    {
        return nullptr;
    }
    while (2 * index <= priorityQueue->elementsNumber)
    {
        size_t leftChild = 2 * index;
        size_t rightChild = 2 * index + 1;
        size_t chosenChild = (rightChild <= priorityQueue->elementsNumber && priorityQueue->keys[rightChild] < priorityQueue->keys[leftChild] ? rightChild : leftChild);
        if (priorityQueue->keys[index] <= priorityQueue->keys[chosenChild])
            break;
        int temp = priorityQueue->keys[index];
        priorityQueue->keys[index] = priorityQueue->keys[chosenChild];
        priorityQueue->keys[chosenChild] = temp;
        temp = priorityQueue->values[index];
        priorityQueue->values[index] = priorityQueue->values[chosenChild];
        priorityQueue->values[chosenChild] = temp;
        index = chosenChild;
    }
    return ok;
}

int enqueue(PriorityQueue* const priorityQueue, const int key, const int value)
{
    if (priorityQueue == NULL)
    {
        return nullptr;
    }
    if (priorityQueue->keys == NULL)
    {
        priorityQueue->keys = calloc(20, sizeof(int));
        priorityQueue->values = calloc(20, sizeof(int));
        if (priorityQueue->keys == NULL || priorityQueue->values == NULL)
        {
            return memoryError;
        }
        priorityQueue->values[1] = value;
        priorityQueue->keys[1] = key;
        priorityQueue->size = 19;
        priorityQueue->elementsNumber = 1;
        return ok;
    }
    if (priorityQueue->elementsNumber == priorityQueue->size)
    {
        priorityQueue->keys = realloc(2 * (priorityQueue->size + 1), sizeof(int));
        priorityQueue->values = realloc(2 * (priorityQueue->size + 1), sizeof(int));
        if (priorityQueue->keys == NULL || priorityQueue->values == NULL)
        {
            return memoryError;
        }
        priorityQueue->size = 2 * priorityQueue->size + 1;
    }
    ++priorityQueue->elementsNumber;
    priorityQueue->keys[priorityQueue->elementsNumber] = key;
    priorityQueue->values[priorityQueue->elementsNumber] = value;
    siftUp(priorityQueue, priorityQueue->elementsNumber);
    return ok;
}

int dequeue(PriorityQueue* const priorityQueue)
{
    if (priorityQueue == NULL)
    {
        return nullptr;
    }
    if (priorityQueue->elementsNumber == 0)
    {
        return emptyPriorityQueue;
    }
    int value = priorityQueue->values[1];
    priorityQueue->keys[1] = priorityQueue->keys[priorityQueue->elementsNumber];
    priorityQueue->keys[priorityQueue->elementsNumber] = 0;
    priorityQueue->values[1] = priorityQueue->values[priorityQueue->elementsNumber];
    priorityQueue->values[priorityQueue->elementsNumber] = 0;
    --priorityQueue->elementsNumber;
    siftDown(priorityQueue, 1);
    return value;
}

void deletePriorityQueue(PriorityQueue** priorityQueue)
{
    if (priorityQueue == NULL || *priorityQueue == NULL)
    {
        return;
    }
    if ((*priorityQueue)->keys != NULL)
    {
        free((*priorityQueue)->keys);
        free((*priorityQueue)->values);
    }
    free(*priorityQueue);
    *priorityQueue = NULL;
}