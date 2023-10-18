#include "CharStack.h"

#include <stdlib.h>

struct CharStack
{
	char value;
	struct CharStack* previous;
};

int pushChar(CharStack** head, char value)
{
	CharStack* newHead = malloc(sizeof(CharStack));
	if (newHead == NULL)
	{
		return -1;
	}
	newHead->value = value;
	newHead->previous = *head;
	*head = newHead;
	return 0;
}

int popChar(CharStack** head)
{
	if (*head == NULL)
	{
		return -1;
	}
	CharStack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return 0;
}

char topChar(CharStack** head)
{
	return (*head)->value;
}

void clearChar(CharStack** head)
{
	while (*head != NULL)
	{
		CharStack* trash = *head;
		*head = (*head)->previous;
		free(trash);
	}
}
