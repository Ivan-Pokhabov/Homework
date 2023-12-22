#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEY_SIZE 100

struct ListElement
{
	int key;
	int value;
	struct ListElement* next;
};

struct List
{
	ListElement* head;
	ListElement* back;
};

List* createList(void)
{
	return calloc(1, sizeof(List));
}

ListErrorCode addList(List* const list, const int key, const int value)
{
	ListElement* newListElement = calloc(1, sizeof(ListElement));
	if (newListElement == NULL)
	{
		return memoryErrorList;
	}
	newListElement->key = key;
	newListElement->value = value;
	if (list->head == NULL)
	{
		list->head = newListElement;
		list->back = newListElement;
		return okList;
	}
	list->back->next = newListElement;
	list->back = newListElement;
	return okList;
}

ListElement* getFirst(const List* const list)
{
	return list->head;
}

ListElement* nextElement(const ListElement* const listElement)
{
	return listElement->next;
}

void getData(const ListElement* const listElement, int* const key, int* const value)
{
	*key = listElement->key;
	*value = listElement->value;
}

void deleteList(List** const list)
{
	if (*list == NULL)
	{
		return;
	}
	while (!isEmpty(*list))
	{
		ListElement* trash = (*list)->head;
		(*list)->head = (*list)->head->next;
		free(trash);
	}
	free(*list);
	*list = NULL;
}