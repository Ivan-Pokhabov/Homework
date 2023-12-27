#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "FileTask.h"
#include "FileTaskTest.h"

static bool test1(void)
{
    if (solveFileTask("testArray1.txt", "testNumber1.txt", "testOutput1.txt") != ok)
    {
        return false;
    }
    int checkArray[3] = { 1, 2, 3 };
    FILE* output = NULL;
    fopen_s(&output, "testOutput1.txt", "r");
    if (output == NULL)
    {
        return false;
    }
    int arrayNumber = 0;
    for (size_t i = 0; i < 3; ++i)
    {
        if (fscanf_s(output, "%d", &arrayNumber) == 0)
        {
            return false;
        }
        if (arrayNumber != checkArray[i])
        {
            return false;
        }
    }
    return true;
}

static bool test2(void)
{
    if (solveFileTask("testArray2.txt", "testNumber2.txt", "testOutput2.txt") != ok)
    {
        return false;
    }
    FILE* output = NULL;
    fopen_s(&output, "testOutput2.txt", "r");
    if (output == NULL)
    {
        return false;
    }
    int arrayNumber = 0;
    if (fscanf_s(output, "%d", &arrayNumber) != 1)
    {
        return true;
    }    
    return false;
}

bool fileTaskTest(void)
{
    bool tests[2] = { test1(), test2() };
    bool complete = true;
    for (size_t i = 0; i < 2; ++i)
    {
        if (!tests[i])
        {
            complete = false;
            printf("Selection sort does not work with test case %lld\n", i + 1);
        }
    }
    return complete;
}