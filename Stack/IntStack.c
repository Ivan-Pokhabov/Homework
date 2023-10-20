#include "IntStack.h"

#include <stdlib.h>

struct IntStack
{
	int value;
	struct IntStack* previous;
};

IntStackErrorCode pushInt(IntStack** head, int value)
{
	IntStack* newHead = calloc(1, sizeof(IntStack));
	if (newHead == NULL)
	{
		return intMemoryError;
	}
	newHead->value = value;
	newHead->previous = *head;
	*head = newHead;
	return intOk;
}

IntStackErrorCode popInt(IntStack** head)
{
	if (head == NULL || *head == NULL)
	{
		return intNullptr;
	}
	IntStack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return intOk;
}

int topInt(IntStack** head, IntStackErrorCode *errorCode)
{
	if (head == NULL || *head == NULL)
	{
		*errorCode = intNullptr;
		return -1;
	}
	return (*head)->value;
}

IntStackErrorCode clearInt(IntStack** head)
{
	if (head == NULL)
	{
		return intNullptr;
	}
	while (*head != NULL)
	{
		IntStack* trash = *head;
		*head = (*head)->previous;
		free(trash);
	}
	return intOk;
}
