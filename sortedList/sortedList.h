#pragma once

typedef struct SortedList SortedList;

SortedList* createSortedList();

int add(SortedList* sortedList, const int value);

int delete(SortedList* sortedList, const int value);

int front(SortedList* sortedList);

int back(SortedList* sortedList);

int isEmpty(SortedList* sortedList);

void deleteSortedList(SortedList** sortedList);

void printSortedList(SortedList* sortedList);