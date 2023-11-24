#include "fileQsort.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define ARRAY_LENGTH 10000

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

bool isSortedTest(int array[], const int arrayLength)
{
    for (int i = 0; i < arrayLength; i++)
    {
        if (array[i] < array[i - 1])
        {
            return false;
        }
    }
    return true;
}

bool qqsortTest(void)
{
    int array1[ARRAYLENGTH] = { 0 };
    int array2[ARRAYLENGTH] = { 0 };
    int array3[ARRAYLENGTH] = { 0 };
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        array1[i] = i;
        array2[i] = 100000 - i;
        array3[i] = rand() % 1000;
    }
    qqsort(array1, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array1, ARRAYLENGTH))
    {
        printf("Qsort is not working with array1");
        return false;
    }
    qqsort(array2, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array2, ARRAYLENGTH))
    {
        printf("Qsort is not working with array2");
        return false;
    }
    qqsort(array3, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array3, ARRAYLENGTH))
    {
        printf("Qsort is not working with array3(random numbers) :\n");
        for (int i = 0; i < ARRAYLENGTH; i++)
        {
            printf("%d ", array3[i]);
        }
        return false;
    }
    return true;
}

int findMostFrequentElement(int array[], const int arrayLength)
{
    qqsort(array, 0, arrayLength - 1);
    int mostFrequentElement = array[0];
    int mostFrequentElementNumber = 1;
    int currentElementNumber = 1;
    for (int i = 1; i < arrayLength; i++)
    {
        if (array[i] != array[i - 1])
        {
            if (currentElementNumber > mostFrequentElementNumber)
            {
                mostFrequentElementNumber = currentElementNumber;
                mostFrequentElement = array[i - 1];
            }
            currentElementNumber = 0;
        }
        ++currentElementNumber;
    }
    if (currentElementNumber > mostFrequentElementNumber)
    {
        mostFrequentElementNumber = currentElementNumber;
        mostFrequentElement = array[arrayLength - 1];
    }
    return mostFrequentElement;
}

bool findMostFrequentElementTest(void)
{
    int array1[10] = { 0, 9, 8, 0, 0, 7 ,7, 6, 2, 2 };
    int array2[10] = { 1, 0, 1, 0, 1, 0, 1, 1, 1, 0 };
    int randomArray[ARRAYLENGTH] = { 0 };
    randomArrayGeneration(randomArray, ARRAYLENGTH, 1000);
    if (findMostFrequentElement(array1, 10) != 0)
    {
        printf("findMostFrequentElement is not working with array1");
        return false;
    }
    if (findMostFrequentElement(array2, 10) != 1)
    {
        printf("findMostFrequentElement is not working with array2");
        return false;
    }
    int maximumValue = randomArray[0];
    int minimumValue = randomArray[0];
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        if (maximumValue < randomArray[i])
        {
            maximumValue = randomArray[i];
        }
        if (minimumValue > randomArray[i])
        {
            minimumValue = randomArray[i];
        }
    }
    const int countingArrayLength = maximumValue - minimumValue + 1;
    int* countingArray = (int*)calloc(countingArrayLength, sizeof(int));
    if (countingArray == NULL)
    {
        printf("Memory limit error");
        return false;
    }
    int randomArrayMostFrequentElementNumber = 0;
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        countingArray[randomArray[i] - minimumValue]++;
        if (countingArray[randomArray[i] - minimumValue] > randomArrayMostFrequentElementNumber)
        {
            randomArrayMostFrequentElementNumber = countingArray[randomArray[i] - minimumValue];
        }
    }
    if (countingArray[findMostFrequentElement(randomArray, ARRAYLENGTH) - minimumValue] != randomArrayMostFrequentElementNumber)
    {
        printf("%d\n", findMostFrequentElement(randomArray, ARRAYLENGTH));
        printf("%d %d\n", countingArray[findMostFrequentElement(randomArray, ARRAYLENGTH) - minimumValue], randomArrayMostFrequentElementNumber);
        printf("findMostFrequentElement is not working with randomArray : ");
        printArray(randomArray, ARRAYLENGTH);
        free(countingArray);
        return false;
    }
    free(countingArray);
    return true;
}

bool test(void)
{
    if (!qqsortTest() || !findMostFrequentElementTest())
    {
        return 0;
    }
}

int main()
{
    test();
    srand(time(NULL));
    int arraySize = 0;
    int array[10000] = { 0 };
    arrayReader("input.txt", &arraySize, array);
    printf("Array: ");
    printArray(array, arraySize);
    printf("\nThe most frequent number in array is %d", findMostFrequentElement(array, arraySize));
}
