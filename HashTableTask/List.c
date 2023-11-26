#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define KEY_SIZE 100

struct ListElement
{
	char key[KEY_SIZE];
	int value;
	struct ListElement* next;
};

struct List
{
	ListElement* head;
	ListElement* back;
	size_t length;
};

List* createList(void)
{
	return calloc(1, sizeof(List));
}

ListErrorCode add(List* const list, const char* const key, const int value)
{
	ListElement* newListElement = calloc(1, sizeof(ListElement));
	if (newListElement == NULL)
	{
		return memoryErrorList;
	}
	strcpy_s(newListElement->key, KEY_SIZE, key);
	newListElement->value = value;
	++list->length;
	if (isEmpty(list))
	{
		list->head = newListElement;
		list->back = newListElement;
		return okList;
	}
	list->back->next = newListElement;
	list->back = newListElement;
	return okList;
}

ListErrorCode delete(List* const list, const char* const key)
{
	if (isEmpty(list))
	{
		return nullptrList;
	}
	ListElement* currentListElement = list->head;
	--list->length;
	if (strcmp(currentListElement->key, key) == 0)
	{
		list->head = currentListElement->next;
		free(currentListElement);
	}
	else
	{
		while (currentListElement->next->next != NULL && strcmp(currentListElement->key, key) != 0)
		{
			currentListElement = currentListElement->next;
		}
		if (currentListElement->next->next == NULL && strcmp(currentListElement->key, key) != 0)
		{
			return deleteNonexistentElementList;
		}
		if (currentListElement->next->next == NULL)
		{
			list->back = currentListElement;
			free(currentListElement->next);
			list->back->next = NULL;
		}
		else
		{
			ListElement* ListElementToDisorder = currentListElement->next;
			currentListElement->next = currentListElement->next->next;
			free(ListElementToDisorder);
		}
	}
	if (isEmpty(list))
	{
		list->back = NULL;
	}
	return okList;
}

ListElement* findElement(const List* const list, const char* const key)
{
	if (isEmpty(list))
	{
		return NULL;
	}
	ListElement* currentListElement = list->head;
	while (currentListElement != NULL && strcmp(currentListElement->key, key) != 0)
	{
		currentListElement = currentListElement->next;
	}
	return currentListElement;
}

ListErrorCode changeElement(ListElement* const listElement, const int value)
{
	if (listElement == NULL)
	{
		return nullptrList;
	}
	listElement->value = value;
	return okList;
}

bool isEmpty(const List* const list)
{
	return list->head == NULL;
}

int get(const ListElement* const listElement)
{
	return listElement->value;
}

void printList(const List* const list)
{
	ListElement* current = list->head;
	while (current != NULL)
	{
		printf("%s - %d\n", current->key, current->value);
		current = current->next;
	}
}

size_t lengthList(const List* const list)
{
	return list == NULL? 0 : list->length;
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