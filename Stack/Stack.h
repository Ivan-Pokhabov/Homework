#pragma once

typedef struct
{
	int value;
	struct Stack* previous;
} Stack;

int push(Stack** head, const int value);

int pop(Stack** head);

int top(Stack** head);

int clear(Stack** head);