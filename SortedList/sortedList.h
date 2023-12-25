#pragma once

#include <stdbool.h>

typedef enum SortedListErrorCode
{
    ok,
    nullptr,
    memoryError,
    deleteNonexistentElement
} SortedListErrorCode;

typedef struct SortedList SortedList;

SortedList* createSortedList();

SortedListErrorCode add(SortedList* sortedList, const int value);

SortedListErrorCode delete(SortedList* sortedList, const int value);

int front(SortedList* sortedList, SortedListErrorCode* errorCode);

int back(SortedList* sortedList, SortedListErrorCode* errorCode);

bool isEmpty(SortedList* sortedList);

void deleteSortedList(SortedList** sortedList);

void printSortedList(SortedList* sortedList);