#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ARRAYLENGTH 10000

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


void insertionSort(int array[], const int leftBorder, const int rightBorder) {
    for (int k = leftBorder; k < rightBorder + 1; k++)
    {
        for (int i = k; i > 0 && array[i - 1] > array[i]; i--)
        {
            const int swap = array[i];
            array[i] = array[i - 1];
            array[i - 1] = swap;
        }
    }
}

void qsort(int array[], const int leftBorder, const int rightBorder)
{
    if (rightBorder - leftBorder <= 9)
    {
        insertionSort(array, leftBorder, rightBorder);
        return;
    }
    const int supportElement = array[(rightBorder + leftBorder) / 2];
    int leftIndex = leftBorder;
    int rightIndex = rightBorder;
    do
    {
        while (supportElement > array[leftIndex])
        {
            leftIndex++;
        }
        while (supportElement < array[rightIndex])
        {
            rightIndex--;
        }
        if (leftIndex <= rightIndex)
        {
            const int swap = array[leftIndex];
            array[leftIndex] = array[rightIndex];
            array[rightIndex] = swap;
            leftIndex++;
            rightIndex--;
        }
    } while (leftIndex <= rightIndex);
    if (leftBorder < rightIndex)
    {
        qsort(array, leftBorder, rightIndex);
    }
    if (leftIndex < rightBorder)
    {
        qsort(array, leftIndex, rightBorder);
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

bool insertionSortTest(void)
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
    insertionSort(array1, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array1, ARRAYLENGTH))
    {
        printf("Insertion sort is not working with array1");
        return false;
    }
    insertionSort(array2, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array2, ARRAYLENGTH))
    {
        printf("Insertion sort is not working with array2");
        return false;
    }
    insertionSort(array3, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array3, ARRAYLENGTH))
    {
        printf("Insertion sort is not working with array3(random numbers) :\n");
        for (int i = 0; i < ARRAYLENGTH; i++)
        {
            printf("%d ", array3[i]);
        }
        return false;
    }
    return true;
}

bool qsortTest(void)
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
    qsort(array1, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array1, ARRAYLENGTH))
    {
        printf("Qsort is not working with array1");
        return false;
    }
    qsort(array2, 0, ARRAYLENGTH - 1);
    if (!isSortedTest(array2, ARRAYLENGTH))
    {
        printf("Qsort is not working with array2");
        return false;
    }
    qsort(array3, 0, ARRAYLENGTH - 1);
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
    qsort(array, 0, arrayLength - 1);
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
    int maximumValue = -100000000;
    int minimumValue = 0;
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
        return false;
    }
    return true;
}

bool test(void)
{
    if (!qsortTest() || !insertionSortTest() || !findMostFrequentElementTest())
    {
         return 0;
    }
}

int main()
{
    test();
    srand(time(NULL));
    int array[10] = { 0 };
    randomArrayGeneration(array, 10, 10);
    printf("Array: ");
    printArray(array, 10);
    printf("\nThe most frequent number in array is %d", findMostFrequentElement(array, 10));
}
