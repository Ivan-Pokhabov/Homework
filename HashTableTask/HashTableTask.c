#include <stdlib.h>
#include <stdio.h>

#include "HashTable.h"

#define MAX_LENGTH 256

int main()
{
    FILE* file = NULL;
    fopen_s(&file, "input.txt", "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return -1;
    }
    Table* table = createTable();
    HashTableErrorCode errorCode = ok;
    char word[MAX_LENGTH] = { 0 };
    while (fscanf_s(file, "%s", word, 256) == 1)
    {
        errorCode = addToTable(table, word);
        if (errorCode == memoryError)
        {
            printf("Memory error!\n");
            return -2;
        }
    }
    printTable(table);
    printf("Load factor = %f\n", loadFactor(table));
    printf("Max length of list = %d\n", maxLengthList(table));
    printf("Average length of list = %f\n", averageLengthList(table));
    freeTable(&table);
    return 0;
}