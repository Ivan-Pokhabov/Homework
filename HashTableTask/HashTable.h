#pragma once
#include "List.h"

// Struct of Hashtable
typedef struct Table Table;

// Hashtable errors
typedef enum HashTableErrorCode
{
	ok,
	nullptr,
	memoryError,
	deleteNonexistentElement,
	getNonexistentElement
} HashTableErrorCode;

// Create hash table
Table* createTable(void);

// Add word into hash table
HashTableErrorCode addToTable(Table* const table, const char* const word);

// return load factor
float loadFactor(const Table* const table);

// return maximum length of lists
int maxLengthList(const Table* const table);

// return average length of lists
float averageLengthList(const Table* const table);

// print hash table
void printTable(const Table* const table);

// delete hash table
void freeTable(Table** const table);