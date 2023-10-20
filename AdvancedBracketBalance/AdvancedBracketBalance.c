#include "..\Stack\CharStack.h"

#include <stdio.h>
#include <stdbool.h>

typedef enum ErrorCode
{
    ok,
    invalidInput,
    stackError
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

bool isBalanced(FILE* file, ErrorCode *errorCode, CharStackErrorCode *stackErrorCode)
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
            if (pushChar(&bracketStack, symbol) != 0)
            {
                *errorCode = stackError;
                clearChar(&bracketStack);
                return false;
            }
        }
        else if (symbol == ')' || symbol == '}' || symbol == ']')
        {
            if (!bracketCompare(topChar(&bracketStack, stackErrorCode), symbol))
            {
                if (*stackErrorCode != charOk)
                {
                    *errorCode = stackError;
                }
                clearChar(&bracketStack);
                return false;
            }
            popChar(&bracketStack);
        }
        else
        {
            *errorCode = invalidInput;
            clearChar(&bracketStack);
            return false;
        }
        symbol = getc(file);
    }
    if (bracketStack != NULL)
    {
        clearChar(&bracketStack);
        return false;
    }
    clearChar(&bracketStack);
    return true;
}

bool test(void)
{
    FILE* file = NULL;
    fopen_s(&file, "test1.txt", "r");
    ErrorCode errorCode = ok;
    CharStackErrorCode stackErrorCode = charOk;
    bool errors[4] = { true, true, true, true };
    if (!isBalanced(file, &errorCode, &stackErrorCode) || errorCode != ok || stackErrorCode != charOk)
    {
        errors[0] = false;
    }
    fopen_s(&file, "test2.txt", "r");
    if (!isBalanced(file, &errorCode, &stackErrorCode) || errorCode != ok || stackErrorCode != charOk)
    {
        errors[1] = false;
    }
    fopen_s(&file, "test3.txt", "r");
    if (isBalanced(file, &errorCode, &stackErrorCode) || errorCode != ok || stackErrorCode != charOk)
    {
        errors[2] = false;
    }
    fopen_s(&file, "test4.txt", "r");
    if (!isBalanced(file, &errorCode, &stackErrorCode) && errorCode == ok || stackErrorCode != charOk)
    {
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
    CharStackErrorCode stackErrorCode = charOk;
    if (!test())
    {
        return 0;
    }
    printf("Enter your bracket subsequence: ");
    if (isBalanced(stdin, &errorCode, &stackErrorCode))
    {
        printf("Your bracket subsequence is balanced");
    }
    else if (errorCode == invalidInput)
    {
        printf("Your input is invalid");
    }
    else if (errorCode == ok)
    {
        printf("Your bracket subsequence is not balanced");
    }
    else
    {
        if (stackError == charNullptr)
        {
            printf("Passing a null pointer");
        }
        else
        {
            printf("Memory error");
        }
    }
}
