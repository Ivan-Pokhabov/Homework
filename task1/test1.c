#include <stdio.h>﻿
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isPalindrome(const char string[])
{
    int leftIndex = 0;
    int rightIndex = strlen(string) - 1;
    while (leftIndex <= rightIndex)
    {
        while (leftIndex <= rightIndex && string[leftIndex] == ' ')
        {
            ++leftIndex;
        }
        while (leftIndex <= rightIndex && string[rightIndex] == ' ')
        {
            --rightIndex;
        }
        if (rightIndex < leftIndex)
        {
            return true;
        }
        if (string[rightIndex] != string[leftIndex])
        {
            return false;
        }
        ++leftIndex;
        --rightIndex;
    }
    return true;
}
bool test(void)
{
    const char string1[] = "sus amo gus sugoma s u s";
    const char string2[] = "aaaaaaaabaaaaaaa";
    const char string3[] = "           ";
    if (!isPalindrome(string1))
    {
        printf("Solve is not working with string1");
        return false;
    }
    if (isPalindrome(string2))
    {
        printf("Solve is not working with string2");
        return false;
    }
    if (!isPalindrome(string3))
    {
        printf("Solve is not working with string3");
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
    const char string[] = "sus amo gus sugoma s u s";
    if (isPalindrome(string))
    {
        printf("%s is palindrome.", string);
    }
    else
    {
        printf("%s string is not palindrome.", string);
    }
}
