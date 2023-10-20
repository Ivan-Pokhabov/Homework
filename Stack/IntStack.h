#pragma once

//Errors
typedef enum IntStackErrorCode
{
	intOk,
	intNullptr,
	intMemoryError
} IntStackErrorCode;

//Struct of stack consisting of integer numbers
typedef struct IntStack IntStack;

//Adding element into the head of stack
IntStackErrorCode pushInt(IntStack** head, int value);

//Deleting element from the head of stack
IntStackErrorCode popInt(IntStack** head);

//Taking value from the top of stack
int topInt(IntStack** head, IntStackErrorCode* errorCode);

//Clearing all elements of stack 
IntStackErrorCode clearInt(IntStack** head);