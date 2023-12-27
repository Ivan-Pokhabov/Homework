#pragma once

#include <stdbool.h>

// List errors
typedef enum ListErrorCode
{
	okList,
	nullptrList,
	memoryErrorList,
	deleteNonexistentElementList,
	getNonexistentElementList
} ListErrorCode;

// Struct of list's element
typedef struct ListElement ListElement;

// Struct of list of elements
typedef struct List List;

// Function that returns pointer on list
List* createList(void);

// Function of adding new element into list
ListErrorCode addList(List* const list, const int key, const int value);

// Function that returns pointer to the first element of list
ListElement* getFirst(const List* const list);

// Function that returns pointer to next element
ListElement* nextElement(const ListElement* const listElement);

// Function that return value and key of given element
void getData(const ListElement* const listElement, int* const key, int* const value);

// Delete list(free memory)
void deleteList(List** const list);