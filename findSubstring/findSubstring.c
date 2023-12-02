#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readTextFromFile(const FILE* const file, char* text, size_t* const textSize)
{
    size_t writeIndex = 0;
    char newSymbol = getc(file);
    while (newSymbol != EOF)
    {
        if (*textSize == writeIndex)
        {
            char* oldText = text;
            text = realloc(text, (*textSize) * sizeof(char) * 2);
            free(oldText);
            if (text == NULL)
            {
                return -1;
            }
            *textSize *= 2;
        }
        text[writeIndex] = newSymbol;
        newSymbol = getc(file);
        ++writeIndex;
    }
    return 0;
}

void prefixFunction(const char* const string, int* const prefixArray, const size_t stringSize, const size_t maxPrefixSize)
{
    for (size_t i = 1; i < stringSize; i++)
    {
        int currentFuctionValue = prefixArray[i - 1];
        while (((string[i] != string[currentFuctionValue]) || currentFuctionValue == maxPrefixSize) && currentFuctionValue > 0)
        {
            currentFuctionValue = prefixArray[currentFuctionValue - 1];
        }
        prefixArray[i] = currentFuctionValue;
        if (string[i] == string[currentFuctionValue])
        {
            prefixArray[i]++;
        }
    }
}

int findSubstring(const char* const string, const char* const text, const size_t stringSize, const size_t textSize)
{
    const size_t newStringSize = stringSize + textSize;
    char* const newString = calloc(newStringSize, sizeof(char));
    if (newString == NULL)
    {
        return -1;
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
    return -2;
}

int main()
{
    FILE* file = NULL;
    fopen_s(&file, "input.txt", "r");
    if (file == NULL)
    {
        return -1;
    }
    size_t textSize = 100;
    char* const text = calloc(textSize, sizeof(char));
    int errorCode = readTextFromFile(file, text, &textSize);
    if (errorCode != 0)
    {
        free(text);
        return errorCode;
    }
    printf("Enter string: ");
    char* string = calloc(100, sizeof(char));
    if (scanf_s("%s", string, 100) == 0)
    {
        printf("Incorrect input");
        free(text);
        free(string);
        return -3;
    }
    const size_t stringSize = strlen(string);
    char* oldString = string;
    string = realloc(string, stringSize * sizeof(char) + 1);
    free(oldString);
    if (string == NULL)
    {
        return -1;
    }
    int substringIndex = findSubstring(string, text, stringSize, textSize);
    if (substringIndex < 1)
    {
        return substringIndex;
    }
    printf("Your string starts in text from index - %d", substringIndex);
}
