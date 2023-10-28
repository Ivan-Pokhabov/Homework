#include "sortedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct SortedListElement
{
	int value;
	struct SortedListElement* next;
} SortedListElement;

struct SortedList
{
	SortedListElement* head;
	SortedListElement* back;
};

SortedList* createSortedList(void)
{
	return calloc(1, sizeof(SortedList));
}

SortedListErrorCode add(SortedList* sortedList, const int value)
{
	SortedListElement* newSortedListElement = calloc(1, sizeof(SortedListElement));
	if (newSortedListElement == NULL)
	{
		return memoryError;
	}
	newSortedListElement->value = value;
	if (isEmpty(sortedList))
	{
		sortedList->head = newSortedListElement;
		sortedList->back = newSortedListElement;
		return ok;
	}
	if (value < sortedList->head->value)
	{
		newSortedListElement->next = sortedList->head;
		sortedList->head = newSortedListElement;
		return ok;
	}
	SortedListElement* currentSortedListElement = sortedList->head;
	while (currentSortedListElement->next != NULL && value > currentSortedListElement->next->value)
	{
		currentSortedListElement = currentSortedListElement->next;
	}
	if (currentSortedListElement->next == NULL)
	{
		if (value < currentSortedListElement->value)
		{
			newSortedListElement->value = currentSortedListElement->value;
			currentSortedListElement->value = value;
		}
		currentSortedListElement->next = newSortedListElement;
		sortedList->back = newSortedListElement;
		return ok;
	}
	newSortedListElement->next = currentSortedListElement->next;
	currentSortedListElement->next = newSortedListElement;
	return ok;
}

SortedListErrorCode delete(SortedList* sortedList, const int value)
{
	if (isEmpty(sortedList))
	{
		return nullptr;
	}
	SortedListElement* currentListElement = sortedList->head;
	if (currentListElement->value == value)
	{
		sortedList->head = currentListElement->next;
		free(currentListElement);
	}
	else
	{
		while (currentListElement->next != NULL && value > currentListElement->next->value)
		{
			currentListElement = currentListElement->next;
		}
		if (currentListElement->next == NULL || currentListElement->next->value != value)
		{
			return deleteNonexistentElement;
		}
		if (currentListElement->next->next == NULL)
		{
			sortedList->back = currentListElement;
			free(currentListElement->next);
			sortedList->back->next = NULL;
		}
		else
		{
			SortedListElement* listElementToDisorder = currentListElement->next;
			currentListElement->next = currentListElement->next->next;
			free(listElementToDisorder);
		}
	}
	if (isEmpty(sortedList))
	{
		sortedList->back = NULL;
	}
	return ok;
}

bool isEmpty(SortedList* sortedList)
{
	return sortedList->head == NULL;
}

int front(SortedList* sortedList, SortedListErrorCode* errorCode)
{
	if (isEmpty(sortedList))
	{
		errorCode = nullptr;
		return -1;
	}
	return (sortedList->head)->value;
}

int back(SortedList* sortedList, SortedListErrorCode* errorCode)
{
	if (isEmpty(sortedList))
	{
		errorCode = nullptr;
		return -1;
	}
	return (sortedList->back)->value;
}

void printSortedList(SortedList* sortedList)
{
	SortedListElement* current = sortedList->head;
	while (current != NULL)
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}

void deleteSortedList(SortedList** sortedList)
{
	while (!isEmpty(*sortedList)) 
	{
		SortedListElement* trash = (*sortedList)->head;
		(*sortedList)->head = (*sortedList)->head->next;
		free(trash);
	}
	free(*sortedList);
	*sortedList = NULL;
}