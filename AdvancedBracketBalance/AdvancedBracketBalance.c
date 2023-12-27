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
        default:
            return false;
    }
}

bool isBalanced(const char* const bracketSequence, ErrorCode *errorCode, CharStackErrorCode *stackErrorCode)
{
    CharStack* bracketStack = NULL;
    size_t symbolIndex = 0;
    char symbol = bracketSequence[symbolIndex];
    while (symbol != '\0')
    {
        while (symbol == ' ')
        {
            ++symbolIndex;
            symbol = bracketSequence[symbolIndex];
        }
        if (symbol == '\0')
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
        ++symbolIndex;
        symbol = bracketSequence[symbolIndex];
    }
    if (bracketStack != NULL)
    {
        clearChar(&bracketStack);
        return false;
    }
    clearChar(&bracketStack);
    return true;
}

bool test1(void)
{
    FILE* file = NULL;
    fopen_s(&file, "test1.txt", "r");
    if (file == NULL)
    {
        return false;
    }
    ErrorCode errorCode = ok;
    CharStackErrorCode stackErrorCode = charOk;
    char sequence[100] = "";
    fgets(sequence, 100, file);
    fclose(file);
    return !(!isBalanced(sequence, &errorCode, &stackErrorCode) || errorCode != ok || stackErrorCode != charOk);
}

bool test2(void)
{
    FILE* file = NULL;
    fopen_s(&file, "test2.txt", "r");
    if (file == NULL)
    {
        return false;
    }
    ErrorCode errorCode = ok;
    CharStackErrorCode stackErrorCode = charOk;
    char sequence[100] = "";
    fgets(sequence, 100, file);
    fclose(file);
    return !(!isBalanced(sequence, &errorCode, &stackErrorCode) || errorCode != ok || stackErrorCode != charOk);
}

bool test3(void)
{
    FILE* file = NULL;
    fopen_s(&file, "test3.txt", "r");
    if (file == NULL)
    {
        return false;
    }
    ErrorCode errorCode = ok;
    CharStackErrorCode stackErrorCode = charOk;
    char sequence[100] = "";
    fgets(sequence, 100, file);
    fclose(file);
    return !(isBalanced(sequence, &errorCode, &stackErrorCode) || errorCode != ok || stackErrorCode != charOk);
}

bool test4(void)
{
    FILE* file = NULL;
    fopen_s(&file, "test3.txt", "r");
    if (file == NULL)
    {
        return false;
    }
    ErrorCode errorCode = ok;
    CharStackErrorCode stackErrorCode = charOk;
    char sequence[100] = "";
    fgets(sequence, 100, file);
    fclose(file);
    return !(isBalanced(sequence, &errorCode, &stackErrorCode) || errorCode != ok || stackErrorCode != charOk);
}

bool test(void)
{
    bool completeTests = true;
    bool errors[4] = {test1(), test2(), test3(), test4()};
    for (int i = 0; i < 4; ++i)
    {
        if (!errors[i])
        {
            printf("Program is not working with test case %d\n", i + 1);
            completeTests = false;
        }
    }
    return completeTests;
}

int main()
{
    ErrorCode errorCode = ok;
    CharStackErrorCode stackErrorCode = charOk;
    if (!test())
    {
        return -1;
    }
    printf("Enter your bracket subsequence: ");
    char sequence[100] = "";
    gets_s(sequence, 100);
    if (isBalanced(sequence, &errorCode, &stackErrorCode))
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
