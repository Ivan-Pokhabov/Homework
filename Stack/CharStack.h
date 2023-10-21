#pragma once

//Errors
typedef enum CharStackErrorCode
{
	charOk,
	charNullptr,
	charMemoryError
} CharStackErrorCode;

//Struct of stack consisting of chars
typedef struct CharStack CharStack;

//Adding element into the head of stack
CharStackErrorCode pushChar(CharStack** head, char value);

//Deleting element from the head of stack
CharStackErrorCode popChar(CharStack** head);

//Taking value from the top of stack
char topChar(CharStack** head, CharStackErrorCode* errorCode);

//Clearing all elements of stack 
CharStackErrorCode clearChar(CharStack** head);
