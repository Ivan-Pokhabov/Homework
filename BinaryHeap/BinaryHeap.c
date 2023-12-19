#include <stdlib.h>
#include <stdbool.h>

#include "BinaryHeap.h"

struct BinaryHeap
{
    int* keys;
    int* values;
    size_t size;
    size_t elementsNumber;
};

BinaryHeap* createHeap(void)
{
    return calloc(1, sizeof(BinaryHeap));
}

static int siftUp(const BinaryHeap* const heap, size_t index)
{
    if (heap == NULL || heap->keys == NULL)
    {
        return nullptr;
    }
    while (index > 1 && heap->keys[index] < heap->keys[index / 2])
    {
        int temp = heap->keys[index];
        heap->keys[index] = heap->keys[index / 2];
        heap->keys[index / 2] = temp;
        temp = heap->values[index];
        heap->values[index] = heap->values[index / 2];
        heap->values[index / 2] = temp;
        index /= 2;
    }
    return ok;
}

static int siftDown(const BinaryHeap* const heap, size_t index)
{
    if (heap == NULL || heap->keys == NULL)
    {
        return nullptr;
    }
    while (2 * index <= heap->elementsNumber)
    {
        size_t leftChild = 2 * index;
        size_t rightChild = 2 * index + 1;
        size_t chosenChild = (rightChild <= heap->elementsNumber && heap->keys[rightChild] < heap->keys[leftChild] ? rightChild : leftChild);
        if (heap->keys[index] <= heap->keys[chosenChild])
            break;
        int temp = heap->keys[index];
        heap->keys[index] = heap->keys[chosenChild];
        heap->keys[chosenChild] = temp;
        temp = heap->values[index];
        heap->values[index] = heap->values[chosenChild];
        heap->values[chosenChild] = temp;
        index = chosenChild;
    }
    return ok;
}

int add(BinaryHeap* const heap, const int key, const int value)
{
    if (heap == NULL)
    {
        return nullptr;
    }
    if (heap->keys == NULL)
    {
        heap->keys = calloc(20, sizeof(int));
        heap->values = calloc(20, sizeof(int));
        if (heap->keys == NULL || heap->values == NULL)
        {
            return memoryError;
        }
        heap->values[1] = value;
        heap->keys[1] = key;
        heap->size = 19;
        heap->elementsNumber = 1;
        return ok;
    }
    if (heap->elementsNumber == heap->size)
    {
        int* oldKeys = heap->keys;
        heap->keys = realloc(heap->keys, 2 * (heap->size + 1), sizeof(int));
        int* oldValues = heap->values;
        heap->values = realloc(heap->keys, 2 * (heap->size + 1), sizeof(int));
        if (heap->keys == NULL)
        {
            free(oldKeys);
            return memoryError;
        }
        if (heap->values == NULL)
        {
            free(oldValues);
            return memoryError;
        }
        heap->size = 2 * heap->size + 1;
    }
    ++heap->elementsNumber;
    heap->keys[heap->elementsNumber] = key;
    heap->values[heap->elementsNumber] = value;
    siftUp(heap, heap->elementsNumber);
    return ok;
}

int pop(BinaryHeap* const heap, int* const key, int* const value)
{
    if (heap == NULL || heap->keys == NULL)
    {
        return nullptr;
    }
    if (heap->elementsNumber == 0)
    {
        return emptyHeap;
    }
    *key = heap->keys[1];
    *value = heap->values[1];
    heap->keys[1] = heap->keys[heap->elementsNumber];
    heap->keys[heap->elementsNumber] = 0;
    heap->values[1] = heap->values[heap->elementsNumber];
    heap->values[heap->elementsNumber] = 0;
    --heap->elementsNumber;
    siftDown(heap, 1);
    return ok;
}

int build(BinaryHeap* const heap, const int const keys[], const int const values[], const size_t size)
{
    if (heap == NULL)
    {
        return nullptr;
    }
    if (heap->keys != NULL)
    {
        free(heap->keys);
        free(heap->values);
    }
    heap->keys = calloc(size + 1, sizeof(int));
    heap->values = calloc(size + 1, sizeof(int));
    if (heap->keys == NULL || heap->values == NULL)
    {
        return nullptr;
    }
    heap->size = size;
    heap->elementsNumber = size;
    for (size_t i = size; i > 0; --i)
    {
        heap->keys[i] = keys[i - 1];
        heap->values[i] = values[i - 1];
    }
    for (size_t i = size; i > 0; --i)
    {
        siftDown(heap, i);
    }
}

void deleteHeap(BinaryHeap** heap)
{
    if (heap == NULL || *heap == NULL)
    {
        return;
    }
    if ((*heap)->keys != NULL)
    {
        free((*heap)->keys);
        free((*heap)->values);
    }
    free(*heap);
    *heap = NULL;
}

bool isEmpty(BinaryHeap* heap)
{
    return heap->elementsNumber == 0;
}