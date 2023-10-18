#include "..\Stack\CharStack.h"

#include <stdio.h>
#include <stdbool.h>

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

int main()
{
    CharStack* bracketStack = NULL;
    char symbol = getchar();
    while (symbol != '\n' || symbol != EOF)
    {
        while (symbol == ' ')
        {
            symbol = getchar();
        }
        if (symbol == '\n' || symbol == EOF)
        {
            break;
        }
        if (symbol == '(' || symbol == '{' || symbol == '[')
        {
            pushChar(&bracketStack, symbol);
        }
        else if (symbol == ')' || symbol == '}' || symbol == ']')
        {
            if (bracketStack == NULL || !bracketCompare(topChar(&bracketStack), symbol))
            {
                printf("Not balanced");
                return 0;
            }
            popChar(&bracketStack);
        }
        else
        {
            printf("Input is invalid");
        }
        symbol = getchar();
    }
    if (bracketStack != NULL)
    {
        printf("Not balanced");
        clearChar(&bracketStack);
        return 0;
    }
    printf("Balanced");
}
