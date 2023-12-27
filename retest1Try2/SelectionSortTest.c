#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "SelectionSort.h"
#include "SelectionSortTest.h"

static bool test1(void)
{
    int array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int check[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    selectionSort(array);
    for (size_t i = 0; i < 10; ++i)
    {
        if (check[i] != array[i])
        {
            return false;
        }
    }
    return true;
}

static bool test2(void)
{
    int array[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int check[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    selectionSort(array);
    for (size_t i = 0; i < 10; ++i)
    {
        if (check[i] != array[i])
        {
            return false;
        }
    }
    return true;
}

static bool test3(void)
{
    int array[10] = { 0, -1, 0, 1, 0, 0, 0, 1, 1, 1 };
    int check[10] = { -1, 0, 0, 0, 0, 0, 1, 1, 1, 1 };
    selectionSort(array);
    for (size_t i = 0; i < 10; ++i)
    {
        if (check[i] != array[i])
        {
            return false;
        }
    }
    return true;
}

bool selectionSortTest(void)
{
    bool tests[3] = { test1(), test2(), test3() };
    bool complete = true;
    for (size_t i = 0; i < 3; ++i)
    {
        if (!tests[i])
        {
            complete = false;
            printf("Selection sort does not work with test case %lld\n", i + 1);
        }
    }
    return complete;
}