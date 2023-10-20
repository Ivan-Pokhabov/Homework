#include "..\Stack\CharStack.h"

#include <stdio.h>
#include <stdbool.h>

typedef enum ErrorCode
{
    ok,
    invalidInput
} ErrorCode;

bool bracketCompare(char leftBracket, char rightBracket)
{
    switch (leftBracket)
    {
        case '{':
            return rightBracket == '}';
        case '(':
            return rightBracket == ')';
        case '[':
            return rightBracket == ']';
    }
}

bool isBalanced(FILE* file, ErrorCode *errorCode)
{
    CharStack* bracketStack = NULL;
    char symbol = getc(file);
    while (symbol != '\n' || symbol != EOF)
    {
        while (symbol == ' ')
        {
            symbol = getc(file);
        }
        if (symbol == '\n' || symbol == EOF)
        {
            break;
        }
        else if (symbol == '(' || symbol == '{' || symbol == '[')
        {
            pushChar(&bracketStack, symbol);
        }
        else if (symbol == ')' || symbol == '}' || symbol == ']')
        {
            if (bracketStack == NULL || !bracketCompare(topChar(&bracketStack), symbol))
            {
                return false;
            }
            popChar(&bracketStack);
        }
        else
        {
            *errorCode = invalidInput;
            return false;
        }
        symbol = getc(file);
    }
    if (bracketStack != NULL)
    {
        return false;
        clearChar(&bracketStack);
    }
    return true;
}

bool test(void)
{
    FILE* file = NULL;
    fopen_s(&file, "test1.txt", "r");
    ErrorCode errorCode = ok;
    bool errors[4] = { true, true, true, true };
    if (!isBalanced(file, &errorCode) || errorCode != ok)
    {
        printf("Program is not working with test case 1");
        errors[0] = false;
    }
    fopen_s(&file, "test2.txt", "r");
    errorCode = ok;
    if (!isBalanced(file, &errorCode) || errorCode != ok)
    {
        printf("Program is not working with test case 2");
        errors[1] = false;
    }
    fopen_s(&file, "test3.txt", "r");
    errorCode = ok;
    if (isBalanced(file, &errorCode) || errorCode != ok)
    {
        printf("Program is not working with test case 3");
        errors[2] = false;
    }
    fopen_s(&file, "test4.txt", "r");
    errorCode = ok;
    if (!isBalanced(file, &errorCode) && errorCode == ok)
    {
        printf("Program is not working with test case 4");
        errors[3] = false;
    }
    bool compliteTests = true;
    for (int i = 0; i < 4; ++i)
    {
        if (!errors[i])
        {
            printf("Program is not working with test case %d\n", i + 1);
            compliteTests = false;
        }
    }
    return compliteTests;
}

int main()
{
    ErrorCode errorCode = ok;
    if (!test())
    {
        return 0;
    }
    if (isBalanced(stdin, &errorCode))
    {
        printf("Your bracket subsequence is balanced");
    }
    else if (errorCode == invalidInput)
    {
        printf("Your input is invalid");
    }
    else
    {
        printf("Your bracket subsequence is not balanced")
    }
}
