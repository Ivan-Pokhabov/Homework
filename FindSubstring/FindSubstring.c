#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum ErrorCodes
{
    ok,
    memoryError = -19,
    nullptr = -20,
    openFileError = -21,
    incorrectInput = -22
} ErrorCodes;

ErrorCodes readTextFromFile(const FILE* const file, char* text, size_t* const textSize)
{
    if (file == NULL || text == NULL || textSize == NULL)
    {
        return nullptr;
    }
    size_t writeIndex = 0;
    char newSymbol = getc(file);
    while (newSymbol != EOF)
    {
        if (*textSize == writeIndex)
        {
            char* oldBuffer = text;
            text = realloc(text, (*textSize) * sizeof(char) * 2);
            if (text == NULL)
            {
                free(oldBuffer);
                return memoryError;
            }
            *textSize *= 2;
        }
        text[writeIndex] = newSymbol;
        newSymbol = getc(file);
        ++writeIndex;
    }
    *textSize = strlen(text);
    char* oldBuffer = text;
    text = realloc(text, (*textSize + 1) * sizeof(char));
    if (text == NULL)
    {
        free(oldBuffer);
        return memoryError;
    }
    return ok;
}

void prefixFunction(const char* const string, int* const prefixArray, const size_t stringSize, const size_t maxPrefixSize)
{
    for (size_t i = 1; i < stringSize; i++)
    {
        int currentFuctionValue = (i == maxPrefixSize) ? 0 : prefixArray[i - 1];
        while (((string[i] != string[currentFuctionValue])) && currentFuctionValue > 0)
        {
            currentFuctionValue = prefixArray[currentFuctionValue - 1];
        }
        if (string[i] == string[currentFuctionValue])
        {
            prefixArray[i] = (currentFuctionValue == maxPrefixSize) ? currentFuctionValue : currentFuctionValue + 1;
        }
    }
}

int findSubstring(const char* const string, const char* const text, const size_t stringSize, const size_t textSize, ErrorCodes* errorCode)
{
    if (string == NULL || text == NULL)
    {
        *errorCode == nullptr;
        return -2;
    }
    const size_t newStringSize = stringSize + textSize;
    char* const newString = calloc(newStringSize, sizeof(char));
    if (newString == NULL)
    {
        *errorCode = memoryError;
        return -2;
    }
    snprintf(newString, newStringSize, "%s%s", string, text);
    int* const prefixArray = calloc(newStringSize, sizeof(int));
    prefixFunction(newString, prefixArray, newStringSize, stringSize);
    for (size_t i = stringSize; i < newStringSize; ++i)
    {
        if (prefixArray[i] == stringSize)
        {
            free(newString);
            free(prefixArray);
            return i - 2 * (stringSize - 1);
        }
    }
    free(newString);
    free(prefixArray);
    return -1;
}

bool test1(void)
{
    ErrorCodes errorCode = ok;
    return findSubstring("ab", "ba", 2, 2, &errorCode) == -1 && errorCode == ok;
}

bool test2(void)
{
    ErrorCodes errorCode = ok;
    return findSubstring("ab", "baab", 2, 4, &errorCode) == 2 && errorCode == ok;
}

bool test3(void)
{
    ErrorCodes errorCode = ok;
    return findSubstring("ab", "ab", 2, 2, &errorCode) == 0 && errorCode == ok;
}

bool test(void)
{
    bool tests[3] = { test1(), test2(), test3() };
    bool complete = true;
    for (size_t i = 0; i < 3; ++i)
    {
        if (!tests[i])
        {
            complete = false;
            printf("Program does not work with test case ");
        }
    }
}

int main()
{
    FILE* file = NULL;
    fopen_s(&file, "input.txt", "r");
    if (file == NULL)
    {
        return openFileError;
    }
    size_t textSize = 100;
    char* const text = calloc(textSize, sizeof(char));
    if (text == NULL)
    {
        fclose(file);
        return nullptr;
    }
    int errorCode = readTextFromFile(file, text, &textSize);
    fclose(file);
    if (errorCode != 0)
    {
        free(text);
        return errorCode;
    }
    printf("Enter string: ");
    char* string = calloc(100, sizeof(char));
    if (scanf_s("%s", string, 100) == 0)
    {
        free(text);
        free(string);
        return incorrectInput;
    }
    const size_t stringSize = strlen(string);
    char* oldBuffer = string;
    string = realloc(string, (stringSize + 1) * sizeof(char));
    if (string == NULL)
    {
        free(text);
        free(oldBuffer);
        return memoryError;
    }
    ErrorCodes errroCode = ok;
    int substringIndex = findSubstring(string, text, stringSize, textSize, &errorCode);
    if (errorCode != ok)
    {
        free(text);
        free(string);
        return errorCode;
    }
    free(text);
    free(string);
    if (substringIndex == -1)
    {
        printf("Substring does not entered in text");
        return ok;
    }
    printf("Your string starts in text from index - %d", substringIndex);
}
