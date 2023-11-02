#pragma once

#include <stdbool.h>

//Struct of credible errors
typedef enum CycleListErrorCode
{
	ok,
	nullptr,
	memoryError,

} CycleListErrorCode;

//Struct of cycle list
typedef struct CycleList CycleList;

//Function that return pointer on cycle list
CycleList* createCycleList();

//Function of adding element with value by index
CycleListErrorCode add(CycleList** cycleList, const int index, const int value);

//Function of deleting element by index
CycleListErrorCode delete(CycleList** cycleList, const int index);

//Function of getting element by index
int get(CycleList* cycleList, const int index, CycleListErrorCode* errorCode);

//Function for checking list is empty or not
bool isEmpty(CycleList* cycleList, CycleListErrorCode* errorCode);

//Function for delete cycle list
void deleteCycleList(CycleList** cycleList);

//Function for printing cycle list
CycleListErrorCode printCycleList(CycleList* cycleList);

//Function for checking number of elements in cycle list
int elementsNumber(CycleList* cycleList, CycleListErrorCode* errorCode);

//Function for deleting all elements except last with given step
CycleListErrorCode deletingByStepExceptLast(CycleList** cycleList, const int step);