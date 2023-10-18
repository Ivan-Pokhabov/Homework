#include "IntStack.h"

#include <stdlib.h>

struct IntStack
{
	int value;
	struct IntStack* previous;
};

int pushInt(IntStack** head, int value)
{
	IntStack* newHead = malloc(sizeof(IntStack));
	if (newHead == NULL)
	{
		return -1;
	}
	newHead->value = value;
	newHead->previous = *head;
	*head = newHead;
	return 0;
}

int popInt(IntStack** head)
{
	if (*head == NULL)
	{
		return -1;
	}
	IntStack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return 0;
}

int topInt(IntStack** head)
{
	return (*head)->value;
}

void clearInt(IntStack** head)
{
	while (*head != NULL)
	{
		IntStack* trash = *head;
		*head = (*head)->previous;
		free(trash);
	}
}
