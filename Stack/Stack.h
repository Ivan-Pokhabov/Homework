#pragma once

typedef struct
{
	char value;
	struct Stack* previous;
} Stack;

int push(Stack** head, const int value);

int pop(Stack** head);

char top(Stack** head);

int clear(Stack** head);