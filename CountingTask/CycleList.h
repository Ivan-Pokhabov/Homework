#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Struct of credible errors
typedef enum CycleListErrorCode
{
    ok,
    nullptr,
    memoryError,
    getNonExistentElement
} CycleListErrorCode;

// Struct of cycle list
typedef struct CycleList CycleList;

// Struct of element of cycle list
typedef struct CycleListElement CycleListElement;

// Function that return pointer on cycle list
CycleList* createCycleList();

// Function of adding element with value by index
CycleListErrorCode add(CycleList* cycleList, const int index, const int value);

// Function of deleting element by index
CycleListErrorCode delete(CycleList** cycleList, CycleListElement** element, const size_t index);

// Function that returns next element
CycleListElement* next(CycleListElement* element, CycleListErrorCode* errorCode);

// Get pointer to element by index
CycleListElement* getListElement(CycleList* cycleList, const size_t position, CycleListErrorCode* errorCode);

// Function of getting element value by index
int get(CycleList* cycleList, const int index, CycleListErrorCode* errorCode);

// Function for checking list is empty or not
bool isEmpty(CycleList* cycleList, CycleListErrorCode* errorCode);

// Function for delete cycle list
void deleteCycleList(CycleList** cycleList);

// Function for printing cycle list
CycleListErrorCode printCycleList(CycleList* cycleList);