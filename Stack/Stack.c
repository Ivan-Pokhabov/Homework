#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

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

char topChar(CharStack** head)
{
	return (*head)->value;
}

int topInt(IntStack** head)
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

void clearInt(IntStack** head)
{
	while (*head != NULL)
	{
		IntStack* trash = *head;
		*head = (*head)->previous;
		free(trash);
	}
}