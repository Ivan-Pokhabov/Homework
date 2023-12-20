#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INT_SIZE 11
#define OK 0
#define INCORRECT_INPUT -1
#define TEST_DID_NOT_PASSED -2

int compare(const int* num1, const int* num2)
{
    return (*num1 > *num2) ? 1 : -1;
}

int makeMinimumNumber(int number)
{
    if (number <= 0)
    {
        return INCORRECT_INPUT;
    }
    int result = 0;
    int digits[INT_SIZE] = { 0 };
    size_t zerosCount = 0;
    for (size_t i = 0; i < INT_SIZE; ++i)
    {
        digits[i] = -1;
    }
    size_t digitIndex = 0;
    while (number > 0)
    {
        if (number % 10 != 0)
        {
            digits[digitIndex] = number % 10;
            ++digitIndex;
        }
        else
        {
            ++zerosCount;
        }
        number /= 10;
    }
    qsort(digits, INT_SIZE, sizeof(int), compare);
    bool wasNotZeroDigit = false;
    for (size_t i = 0; i < INT_SIZE; ++i)
    {
        if (digits[i] == -1)
        {
            continue;
        }
        if (wasNotZeroDigit && zerosCount != 0)
        {
            while (zerosCount > 0)
            {
                result *= 10;
                --zerosCount;
            }
        }
        result *= 10;
        result += digits[i];
        if (!wasNotZeroDigit)
        {
            wasNotZeroDigit = true;
        }
    }
    return result;
}

bool test1(void)
{
    return makeMinimumNumber(0) == INCORRECT_INPUT;
}

bool test2(void)
{
    return makeMinimumNumber(1001) == 1001;
}

bool test3(void)
{
    return makeMinimumNumber(7611540) == 1014567;
}

bool test(void)
{
    bool tests[3] = { test1(), test2(), test3() };
    bool passed = true;
    for (size_t i = 0; i < 3; ++i)
    {
        if (tests[i] != true)
        {
            passed = false;
            printf("Function does not work with test %lld", i + 1);
        }
    }
    return passed;
}

int main()
{
    if (!test())
    {
        return TEST_DID_NOT_PASSED;
    }
    int number = 51400;
    number = makeMinimumNumber(number);
    if (number == INCORRECT_INPUT)
    {
        printf("Incorrect input");
        return INCORRECT_INPUT;
    }
    printf("Minimum number is %d", number);
    return OK;
}
