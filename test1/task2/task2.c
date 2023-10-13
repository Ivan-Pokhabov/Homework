#include <stdio.h>﻿
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAYLENGTH 100

void printArray(int array[], const int arrayLength)
{
    if (arrayLength == 0)
    {
        printf("None");
        return;
    }
    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d ", array[i]);
    }
}

void bubbleSort(int array[], const int arrayLength)
{
    for (int i = 0; i < arrayLength; i += 2)
    {
        for (int j = 0; j < arrayLength - i - 1; j += 2)
        {
            if (array[j] > array[j + 2])
            {
                int swap = array[j];
                array[j] = array[j + 2];
                array[j + 2] = swap;
            }
        }
    }
}

bool isSortedTest(int array[], const int arrayLength)
{
    for (int i = 0; i < arrayLength; i += 2)
    {
        if (array[i] < array[i - 2])
        {
            return false;
        }
    }
    return true;
}

void randomArrayGeneration(int array[], const int arrayLength, const int module)
{
    srand(time(NULL));
    for (int i = 0; i < arrayLength; i++)
    {
        array[i] = rand() % module;
        if (i % 139 == 0)
        {
            array[i] *= -1;
        }
    }
}

void test(void)
{
    int array1[ARRAYLENGTH] = { 0 };
    int array2[ARRAYLENGTH] = { 0 };
    int array3[10] = { 0 };
    int array4[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int array5[2] = { 2, 1 };
    int array6[1] = { 0 };
    bubbleSort(array1, ARRAYLENGTH);
    bubbleSort(array2, ARRAYLENGTH);
    bubbleSort(array3, 10);
    bubbleSort(array4, 10);
    bubbleSort(array5, 2);
    bubbleSort(array6, 1);
    if (!isSortedTest(array1, ARRAYLENGTH))
    {
        printf("Solve is not working with array :\n");
        printArray(array1, ARRAYLENGTH);
        return false;
    }
    if (!isSortedTest(array2, ARRAYLENGTH))
    {
        printf("Solve is not working with array :\n");
        printArray(array2, ARRAYLENGTH);
        return false;
    }
    if (!isSortedTest(array3, 10))
    {
        printf("Solve is not working with array :\n");
        printArray(array3, 10);
        return false;
    }
    if (!isSortedTest(array4, 10))
    {
        printf("Solve is not working with array :\n");
        printArray(array4, 10);
        return false;
    }
    if (!isSortedTest(array5, 2))
    {
        printf("Solve is not working with array :\n");
        printArray(array5, 2);
        return false;
    }
    if (!isSortedTest(array6, 1))
    {
        printf("Solve is not working with array :\n");
        printArray(array6, 1);
        return false;
    }
    return true;
}

int main()
{
    if (!test)
    {
        return 0;
    }
    int array[] = { 5, 4, 3, 2, 1 };
    printf("Array is ");
    printArray(array, 5);
    printf("\nSorted array is ");
    bubbleSort(array, 5);
    printArray(array, 5);
}
