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
ListErrorCode add(List* const list, const char* const key, const int value);

// Function of deleting element from list
ListErrorCode delete(List* const list, const char* const key);

// Function that returns element of list by given key. If this element does not exist return NULL
ListElement* findElement(const List* const list, const char* const key);

// Function that change value of given element
ListErrorCode changeElement(ListElement* const listElement, const int value);

// Function that return value of given element
int get(const ListElement* const listElement);

// Check empty list or not
bool isEmpty(const List* const list);

// Print list into console
void printList(const List* const list);

// Return length of list
size_t lengthList(const List* const list);

// Delete list(free memory)
void deleteList(List** const list);
