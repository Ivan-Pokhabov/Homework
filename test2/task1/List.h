#pragma once

#include <stdbool.h>

//Error codes
typedef enum ListErrorCode
{
	ok,
	nullptr,
	memoryError,
	deleteNonexistentElement,
	getNonExistentElement
} ListErrorCode;

typedef struct ListElement ListElement;

//List struct
typedef struct List List;

//Create pointer to List
List* createList(void);

//Get index
ListElement* getListElement(List* list, const size_t position, ListErrorCode* errorCode);

//Add element to list
ListErrorCode add(List* list, const int value);

//Get value from element
int getValue(ListElement* element, ListErrorCode* errorCode);

//Delete element from list except first
ListErrorCode delete(ListElement** element, const size_t position);

//Check empty list or nit
bool isEmpty(List* list);

//Print list
void printList(List* list);

//Delete list
void deleteList(List** list);
