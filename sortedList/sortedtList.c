#include "sortedList.h"

#include <stdio.h>
#include <stdlib.h>

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

int add(SortedList* sortedList, const int value)
{
	SortedListElement* newSortedListElement = calloc(1, sizeof(SortedListElement));
	if (newSortedListElement == NULL)
	{
		return -1;
	}
	newSortedListElement->value = value;
	if (isEmpty(sortedList))
	{
		sortedList->head = newSortedListElement;
		sortedList->back = newSortedListElement;
		return 0;
	}
	SortedListElement* currentSortedListElement = sortedList->head;
	while (currentSortedListElement->next != NULL && value < currentSortedListElement->value)
	{
		currentSortedListElement = currentSortedListElement->next;
	}
	if (currentSortedListElement->next == NULL)
	{
		currentSortedListElement->next = newSortedListElement;
		sortedList->back = newSortedListElement;
		return 0;
	}
	newSortedListElement->next = currentSortedListElement->next;
	currentSortedListElement->next = newSortedListElement;
	return 0;
}

int delete(SortedList* sortedList, const int value)
{
	if (isEmpty(sortedList))
	{
		return -1;
	}
	SortedListElement* currentListElement = sortedList->head;
	if (currentListElement->value == value)
	{
		sortedList->head = currentListElement->next;
		free(currentListElement);
	}
	else
	{
		while (currentListElement->next != NULL && value < currentListElement->next->value)
			{
				currentListElement = currentListElement->next;
			}
			if (currentListElement->next == NULL || currentListElement->next->value != value)
			{
				return -2;
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
	return 0;
}

int isEmpty(SortedList* sortedList)
{
	return sortedList->head == NULL;
}

int front(SortedList* sortedList)
{
	return (sortedList->head)->value;
}

int back(SortedList* sortedList)
{
	return (sortedList->back)->value;
}

void printSortedList(SortedList* sortedList)
{
	if (sortedList == NULL)
	{
		return;
	}
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
		//delete(*sortedList); TO DO
	}
	free(*sortedList);
	*sortedList = NULL;
}