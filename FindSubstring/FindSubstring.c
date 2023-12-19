#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ErrorCodes
{
    ok,
    memoryError = -19,
    nullptr = -20,
    openFileError = -21,
    incorrectInput = -22
};

int readTextFromFile(const FILE* const file, char* text, size_t* const textSize)
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
    return 0;
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

int findSubstring(const char* const string, const char* const text, const size_t stringSize, const size_t textSize)
{
    if (string == NULL || text == NULL)
    {
        return nullptr;
    }
    const size_t newStringSize = stringSize + textSize;
    char* const newString = calloc(newStringSize, sizeof(char));
    if (newString == NULL)
    {
        return memoryError;
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
    string = realloc(string, (stringSize + 1) * sizeof(char));
    if (string == NULL)
    {
        free(text);
        return memoryError;
    }
    int substringIndex = findSubstring(string, text, stringSize, textSize);
    free(text);
    free(string);
    if (substringIndex < -1)
    {
        return substringIndex;
    }
    if (substringIndex == -1)
    {
        printf("Substring does not entered in text");
        return 0;
    }
    printf("Your string starts in text from index - %d", substringIndex);
}
