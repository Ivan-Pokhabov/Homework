#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

int push(Stack** head, const int value)
{
	Stack* newHead = malloc(sizeof(Stack));
	if (newHead == NULL)
	{
		return -1;
	}
	newHead->value= value;
	newHead->previous = *head;
	*head = newHead;
	return 0;
}

int pop(Stack** head)
{
	if (head == NULL)
	{
		return 1;
	}
	Stack* trash = malloc(sizeof(Stack));
	if (trash == NULL)
	{
		return -1;
	}
	trash = *head;
	*head = (*head)->previous;
	free(trash);
	return 0;
}

int top(Stack* head, int error)
{
	if (head == NULL)
	{
		error = 1;
	}
	return head->value;
}

int clear(Stack** head)
{
	while (*head != NULL)
	{
		if (head == NULL)
		{
			return 1;
		}
		Stack* trash = malloc(sizeof(Stack));
		if (trash == NULL)
		{
			return -1;
		}
		trash = *head;
		*head = (*head)->previous;
		free(trash);
	}
	return 0;
}