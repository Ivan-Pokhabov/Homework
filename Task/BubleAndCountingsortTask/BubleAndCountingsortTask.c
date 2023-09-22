#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARRAYLENGTH 100000

void bubbleSort(int array[])
{
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        for (int j = 0; j < ARRAYLENGTH - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int swap = array[j];
                array[j] = array[j + 1];
                array[j + 1] = swap;
            }
        }
    }
}

void countingSort(int array[])
{
    int maximumValue = -100000000;
    int nonNegativeAddition = 100000000;
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        maximumValue = max(maximumValue, array[i]);
        nonNegativeAddition = min(nonNegativeAddition, array[i]);
    }
    nonNegativeAddition = max(0, nonNegativeAddition);
    const int countingArrayLength = maximumValue + nonNegativeAddition + 1;
    int* countingArray = (int*)malloc((countingArrayLength) * sizeof(int));
    for (int i = 0; i < countingArrayLength; i++)
    {
        countingArray[i] = 0;
    }
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        countingArray[array[i]]++;
    }
    int currentIndex = 0;
    for (int i = 0; i < countingArrayLength; i++)
    {
        for (int j = currentIndex; j < countingArray[i] + currentIndex; j++)
        {
            array[j] = i - nonNegativeAddition;
        }
        currentIndex += countingArray[i];
    }
    free(countingArray);
}

void printArray(int array[])
{
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        printf("%d ", array[i]);
    }
}

double timeCheckBubbleSort(int array[])
{
    clock_t startBubleSort = clock();
    bubbleSort(array);
    clock_t endBubleSort = clock();
    return (double)(endBubleSort - startBubleSort) / CLK_TCK;
}

double timeCheckCountingSort(int array[])
{
    clock_t startCountingSort = clock();
    countingSort(array);
    clock_t endCountingSort = clock();
    return (double)(endCountingSort - startCountingSort) / CLK_TCK;
}

void initializationIncreasingArrays(int array[], int arrayCopy[])
{
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        array[i] = i;
        arrayCopy[i] = i;
    }
}

void initializationDecreasingArrays(int array[], int arrayCopy[])
{
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        array[i] = ARRAYLENGTH - i;
        arrayCopy[i] = ARRAYLENGTH - i;
    }
}

void initializationRandomArrays(int array[], int arrayCopy[])
{
    srand(time(NULL));
    for (int i = 0; i < ARRAYLENGTH; i++)
    {
        array[i] = rand();
        arrayCopy[i] = array[i];
    }
}

int main()
{
    int array[ARRAYLENGTH] = { 0 };
    int arrayCopy[ARRAYLENGTH] = { 0 };
    printf("Array of zeros time: bubble sort - %2.3f, counting sort - %2.3f\n", timeCheckBubbleSort(array), timeCheckCountingSort(arrayCopy));
    initializationIncreasingArrays(array, arrayCopy);
    printf("Increasing time: bubble sort - %2.3f, counting sort - %2.3f\n", timeCheckBubbleSort(array), timeCheckCountingSort(arrayCopy));
    initializationDecreasingArrays(array, arrayCopy);
    printf("Decreasing time: bubble sort - %2.3f, counting sort - %2.3f\n", timeCheckBubbleSort(array), timeCheckCountingSort(arrayCopy));
    initializationRandomArrays(array, arrayCopy);
    printf("Array of random numbers time: bubble sort - %2.3f, counting sort - %2.3f", timeCheckBubbleSort(array), timeCheckCountingSort(arrayCopy));
}