#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SelectionSort.h"
#include "SelectionSortTest.h"
#include "FileTask.h"
#include "FileTaskTest.h"

#define TEST_NOT_COMPLETE -1
#define INCORRECT_INPUT -2

unsigned int sumOfFibonacci(void)
{
    unsigned int sum = 0;
    unsigned int firstNumber = 1;
    unsigned int secondNumber = 1;
    while (firstNumber + secondNumber <= (unsigned int)1e6)
    {
        unsigned int temp = firstNumber;
        firstNumber += secondNumber;
        secondNumber = temp;
        if (firstNumber % 2 == 0)
        {
            sum += firstNumber;
        }
        
    }
    return sum;
}

bool testFibonacci(void)
{
    return sumOfFibonacci() == 1089154;
}

int main()
{
    if (!testFibonacci())
    {
        return TEST_NOT_COMPLETE;
    }
    printf("Fibonacci task : %u\n", sumOfFibonacci());
    if (!selectionSortTest())
    {
        return TEST_NOT_COMPLETE;
    }
    int array[10] = { 0 };
    printf("Selection sort task:\nEnter array of 10 numbers : ");
    for (size_t i = 0; i < 10; ++i)
    {
        if (scanf_s("%d", &array[i]) == 0)
        {
            return INCORRECT_INPUT;
        }
    }
    selectionSort(array);
    printf("Sorted array : ");
    for (size_t i = 0; i < 10; ++i)
    {
        printf("%d ", array[i]);
    }
    solveFileTask("f.txt", "g.txt", "h.txt");
    if (!fileTaskTest())
    {
        return TEST_NOT_COMPLETE;
    }
}

