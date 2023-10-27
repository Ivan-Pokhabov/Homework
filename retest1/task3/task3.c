#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SYMBOL_NUMBERS 256

void charsCounting(FILE* file, int array[SYMBOL_NUMBERS])
{
    char symbol = getc(file);
    while (symbol != EOF)
    {
        ++array[symbol - '\0'];
        symbol = getc(file);
    }
}

bool tests(void)
{
    FILE* file = NULL;
    fopen_s(&file, "test1.txt", "r");
    if (file == NULL)
    {
        printf("File test2.txt did not open");
        return false;
    }
    int array[SYMBOL_NUMBERS] = { 0 };
    charsCounting(file, array);
    int arrayCheck[SYMBOL_NUMBERS] = { 0 };
    arrayCheck[10] = 1;
    bool testCases[2] = { true, true };
    for (int i = 0; i < SYMBOL_NUMBERS; ++i)
    {
        if (array[i] != arrayCheck[i])
        {
            testCases[0] = false;
        }
        array[i] = 0;
        arrayCheck[i] = 0;
    }
    fopen_s(&file, "test2.txt", "r");
    if (file == NULL)
    {
        printf("File test2.txt did not open");
        return false;
    }
    charsCounting(file, array);
    arrayCheck[49] = 1;
    arrayCheck[50] = 1;
    arrayCheck[51] = 1;
    for (int i = 0; i < SYMBOL_NUMBERS; ++i)
    {
        if (array[i] != arrayCheck[i])
        {
            testCases[0] = false;
        }
    }
    bool compliteTests = true;
    for (int i = 0; i < 4; ++i)
    {
        if (!testCases[i])
        {
            printf("Program is not working with test case %d\n", i + 1);
            compliteTests = false;
        }
    }
    return compliteTests;

}

int main()
{
    FILE* file = NULL;
    if (!tests())
    {
        return -2;
    }
    fopen_s(&file, "test1.txt", "r");
    if (file == NULL)
    {
        printf("File test1.txt did not open");
        return -1;
    }
    int array[SYMBOL_NUMBERS] = { 0 };
    charsCounting(file, array);
    for (int i = 0; i < SYMBOL_NUMBERS; ++i)
    {
        if (array[i] != 0)
        {
            printf("%c - %d\n", i + '\0', array[i]);
        }

    }
}
