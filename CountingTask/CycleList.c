#include "CycleList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct CycleListElement
{
	int value;
	struct CycleListElement* next;
} CycleListElement;

struct CycleList
{
	CycleListElement* head;
	int elementsNumber;
};

CycleList* createCycleList(void)
{
	return calloc(1, sizeof(CycleList));
}

CycleListErrorCode add(CycleList** cycleList, const int index, const int value)
{
	if (cycleList == NULL)
	{
		return nullptr;
	}
	CycleListElement* newCycleListElement = calloc(1, sizeof(CycleListElement));
	if (newCycleListElement == NULL)
	{
		return memoryError;
	}
	++(*cycleList)->elementsNumber;
	newCycleListElement->value = value;
	CycleListErrorCode errorCode = ok;
	if (isEmpty(*cycleList, &errorCode))
	{
		if (errorCode == nullptr)
		{
			return nullptr;
		}
		newCycleListElement->next = newCycleListElement;
		(*cycleList)->head = newCycleListElement;
		return ok;
	}
	if (index == 1)
	{
		newCycleListElement->next = (*cycleList)->head;
		(*cycleList)->head = newCycleListElement;
		return ok;
	}
	CycleListElement* currentCycleListElement = (*cycleList)->head;
	int currentIndex = 0;
	while (currentIndex < index - 2)
	{
		currentCycleListElement = currentCycleListElement->next;
		++currentIndex;
	}
	newCycleListElement->next = currentCycleListElement->next;
	currentCycleListElement->next = newCycleListElement;
	return ok;
}

CycleListErrorCode delete(CycleList** cycleList, const int index)
{
	CycleListErrorCode errorCode = ok;
	if (cycleList == NULL || isEmpty(*cycleList, &errorCode))
	{
		return nullptr;
	}
	--(*cycleList)->elementsNumber;
	CycleListElement* currentListElement = (*cycleList)->head;
	if (index == 1)
	{
		CycleListElement* listElementToDisorder = (*cycleList)->head;
		(*cycleList)->head = (*cycleList)->head->next;
		free(listElementToDisorder);
		return ok;
	}
	int currentIndex = 0;
	while (currentIndex < index - 2)
	{
		currentListElement = currentListElement->next;
		++currentIndex;
	}
	CycleListElement* listElementToDisorder = currentListElement->next;
	currentListElement->next = currentListElement->next->next;
	if ((*cycleList)->elementsNumber != 0)
	{
		if (listElementToDisorder == (*cycleList)->head)
		{
			(*cycleList)->head = (*cycleList)->head->next;
		}
	}
	free(listElementToDisorder);
	return ok;
}

bool isEmpty(CycleList* cycleList, CycleListErrorCode* errorCode)
{
	if (cycleList == NULL)
	{
		*errorCode = nullptr;
		return true;
	}
	return cycleList->head == NULL;
}

int get(CycleList* cycleList, const int index, CycleListErrorCode* errorCode)
{
	if (isEmpty(cycleList, errorCode))
	{
		*errorCode = nullptr;
		return -1;
	}
	int currentIndex = 0;
	CycleListElement* currentCycleListElement = cycleList->head;
	while (currentIndex < index - 1)
	{
		currentCycleListElement = currentCycleListElement->next;
		++currentIndex;
	}
	return currentCycleListElement->value;
}

CycleListErrorCode printCycleList(CycleList* cycleList)
{
	if (cycleList == NULL)
	{
		return nullptr;
	}
	CycleListElement* current = cycleList->head;
	int currentIndex = 0;
	while (currentIndex < cycleList->elementsNumber)
	{
		printf("%d ", current->value);
		current = current->next;
		++currentIndex;
	}
	printf("\n");
	return ok;
}

void deleteCycleList(CycleList** cycleList)
{
	if (cycleList == NULL || *cycleList == NULL)
	{
		return;
	}
	while ((*cycleList)->elementsNumber > 0)
	{
		--(*cycleList)->elementsNumber;
		CycleListElement* trash = (*cycleList)->head;
		(*cycleList)->head = (*cycleList)->head->next;
		free(trash);
	}
	free(*cycleList);
	*cycleList = NULL;
}

int elementsNumber(CycleList* cycleList, CycleListErrorCode* errorCode)
{
	if (cycleList == NULL)
	{
		*errorCode = nullptr;
	}
	return cycleList->elementsNumber;
}

CycleListErrorCode deletingByStepExceptLast(CycleList** cycleList, const int step)
{
	CycleListErrorCode errorCode = ok;
	
	if (cycleList == NULL || isEmpty(*cycleList, &errorCode))
	{
		return nullptr;
	}
	CycleListElement* currentListElement = (*cycleList)->head;
	while ((*cycleList)->elementsNumber > 1)
	{
		if (step > 1)
		{
			for (int i = 0; i < step - 2; ++i)
			{
				currentListElement = currentListElement->next;
			}
			CycleListElement* listElementToDisorder = currentListElement->next;
			currentListElement->next = currentListElement->next->next;
			if (listElementToDisorder == (*cycleList)->head)
			{
				(*cycleList)->head = (*cycleList)->head->next;
			}
			free(listElementToDisorder);
			--(*cycleList)->elementsNumber;
			currentListElement = currentListElement->next;
		}
		else
		{
			--(*cycleList)->elementsNumber;
			CycleListElement* trash = (*cycleList)->head;
			(*cycleList)->head = (*cycleList)->head->next;
			free(trash);
		}
	}
	return ok;
}