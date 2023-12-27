#include <stdlib.h>
#include <string.h>

#include "HashTable.h"
#include "List.h"

#define HASH_SIZE 113

typedef struct Table
{
    size_t amount;
    size_t size;
    List* hashes[HASH_SIZE];
} Table;

size_t hash(const char* const key)
{
    size_t result = 0;
    for (size_t i = 0; key[i] != '\0'; ++i)
    {
        result = (key[i] + result * 13) % HASH_SIZE;
    }
    return result;
}

Table* createTable(void)
{
    Table* new = calloc(1, sizeof(Table));
    if (new == NULL)
    {
        return NULL;
    }

    new->size = HASH_SIZE;
    return new;
}

HashTableErrorCode addToTable(Table* const table, const char* const word)
{
    if (table == NULL)
    {
        return nullptr;
    }
    List* bucket = table->hashes[hash(word)];
    
    if (bucket == NULL)
    {
        table->hashes[hash(word)] = createList();
        int errorCode = add(table->hashes[hash(word)], word, 1);
        if (errorCode != ok)
        {
            return errorCode;
        }
        ++table->amount;
        return ok;
    }
    ListElement* entry = findElement(bucket, word);
    if (entry == NULL)
    {
        int errorCode = add(bucket, word, 1);
        if (errorCode != ok)
        {
            return errorCode;
        }
        ++table->amount;
    }
    else
    {
        changeElement(entry, get(entry) + 1);
    }
    return ok;
}

float loadFactor(const Table* const table)
{
    if (table == NULL)
    {
        return -1.0;
    }
    return (float)table->amount / (float)table->size;
}

int maxLengthList(const Table* const table)
{
    if (table == NULL)
    {
        return -1;
    }
    int maxLength = 0;
    for (int i = 0; i < table->size; ++i)
    {
        if ((int)lengthList(table->hashes[i]) > maxLength)
        {
            maxLength = (int)lengthList(table->hashes[i]);
        }
    }
    return maxLength;
}

float averageLengthList(const Table* const table)
{
    if (table == NULL)
    {
        return -1.0;
    }
    int numberOfLists = 0;
    int numberOfNodes = 0;
    for (int i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] != NULL)
        {
            ++numberOfLists;
            numberOfNodes += (int)lengthList(table->hashes[i]);
        }
    }
    return (float)numberOfNodes / (float)numberOfLists;
}

void printTable(const Table* const table)
{
    if (table == NULL)
    {
        return;
    }
    for (int i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            continue;
        }
        printList(table->hashes[i]);
    }
}

void freeTable(Table** const table)
{
    if (table == NULL)
    {
        return;
    }
    for (int i = 0; i < (*table)->size; ++i)
    {
        deleteList(&(*table)->hashes[i]);
    }
    free(*table);
    *table = NULL;
}