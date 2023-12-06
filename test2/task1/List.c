#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct ListElement
{
	int value;
	struct ListElement* next;
} ListElement;

struct List
{
	ListElement* head;
	ListElement* back;
};

List* createList(void)
{
	return calloc(1, sizeof(List));
}

ListErrorCode add(List* list, const int value)
{
	ListElement* newListElement = calloc(1, sizeof(ListElement));
	if (newListElement == NULL)
	{
		return memoryError;
	}
	newListElement->value = value;
	if (isEmpty(list))
	{
		list->head = newListElement;
		list->back = newListElement;
		return ok;
	}
	list->back->next = newListElement;
	list->back = newListElement;
	return ok;
}

ListElement* getListElement(List* list, const size_t position, ListErrorCode* errorCode)
{
	if (list == NULL || isEmpty(list))
	{
		*errorCode = nullptr;
		return NULL;
	}
	ListElement* current = list->head;
	for (size_t i = 0; i < position; ++i)
	{
		current = current->next;
		if (current == NULL)
		{
			*errorCode = getNonExistentElement;
			return NULL;
		}
	}
	return current;
}

int getValue(ListElement* element, ListErrorCode* errorCode)
{
	if (element == NULL)
	{
		*errorCode = nullptr;
		return -1;
	}
	return element->value;
}

ListErrorCode delete(ListElement** element, const size_t position)
{
	if (element == NULL || *element == NULL)
	{
		return nullptr;
	}
	for (size_t i = 1; i < position; ++i)
	{
		*element = (*element)->next;
		if (*element == NULL)
		{
			return deleteNonexistentElement;
		}
	}
	if ((*element)->next == NULL)
	{
		return deleteNonexistentElement;
	}
	ListElement* elementToDisorder = (*element)->next;
	(*element)->next = (*element)->next->next;
	free(elementToDisorder);
	(*element) = (*element)->next;
	return ok;
}

bool isEmpty(List* list)
{
	return list->head == NULL;
}

void printList(List* list)
{
	if (list == NULL)
	{
		return;
	}
	ListElement* current = list->head;
	while (current != NULL)
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}

void deleteList(List** list)
{
	while (!isEmpty(*list))
	{
		ListElement* trash = (*list)->head;
		(*list)->head = (*list)->head->next;
		free(trash);
	}
	free(*list);
	*list = NULL;
}
