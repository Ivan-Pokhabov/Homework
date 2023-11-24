#include "fileQsort.h"

#include <stdio.h>

void qqsort(int array[], const int leftBorder, const int rightBorder)
{
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
        qqsort(array, leftBorder, rightIndex);
    }
    if (leftIndex < rightBorder)
    {
        qqsort(array, leftIndex, rightBorder);
    }
}

void arrayReader(const char *fileName, int *arraySize, int array[])
{
    errno_t err;
    FILE* file;
    err = fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        printf("file not found!");
        return;
    }
    const int readBytes = fscanf_s(file, "%d", arraySize);
    if (!array)
    {
        printf("memory dead");
        return;
    }
    for (int i = 0; i < *arraySize; ++i)
    {
        int x = 0;
        fscanf_s(file, "%d", &array[i]);
    } 
}