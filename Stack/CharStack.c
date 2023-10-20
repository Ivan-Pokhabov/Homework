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
		return memoryError;
	}
	newHead->value = value;
	newHead->previous = *head;
	*head = newHead;
	return ok;
}

CharStackErrorCode popChar(CharStack** head)
{
	if (head == NULL || *head == NULL)
	{
		return nullptr;
	}
	CharStack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return ok;
}

char topChar(CharStack** head, CharStackErrorCode *errorCode)
{
	if (head == NULL || *head == NULL)
	{
		*errorCode = nullptr;
		return 'x';
	}
	return (*head)->value;
}

CharStackErrorCode clearChar(CharStack** head)
{
	if (head == NULL)
	{
		return nullptr;
	}
	while (*head != NULL)
	{
		CharStack* trash = *head;
		*head = (*head)->previous;
		free(trash);
	}
	return ok;
}
