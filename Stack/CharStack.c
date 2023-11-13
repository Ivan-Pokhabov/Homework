#include "CharStack.h"

#include <stdlib.h>

struct CharStack
{
	char value;
	struct CharStack* previous;
};

CharStackErrorCode pushChar(CharStack** head, char value)
{
	CharStack* newHead = malloc(sizeof(CharStack));
	if (newHead == NULL)
	{
		return charMemoryError;
	}
	newHead->value = value;
	newHead->previous = *head;
	*head = newHead;
	return charOk;
}

CharStackErrorCode popChar(CharStack** head)
{
	if (head == NULL || *head == NULL)
	{
		return charNullptr;
	}
	CharStack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return charOk;
}

char topChar(CharStack** head, CharStackErrorCode *errorCode)
{
	if (head == NULL || *head == NULL)
	{
		*errorCode = charNullptr;
		return 'x';
	}
	return (*head)->value;
}

CharStackErrorCode clearChar(CharStack** head)
{
	if (head == NULL)
	{
		return charNullptr;
	}
	while (*head != NULL)
	{
		CharStack* trash = *head;
		*head = (*head)->previous;
		free(trash);
	}
	return charOk;
}
