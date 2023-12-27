#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "Lexer.h"

typedef enum Stage
{
    nothing = 0,
    firstDigit = 1,
    dot = 2,
    secondDigit = 3,
    stateOnE = 4,
    plusOrMinus = 5,
    thirdDigit = 6,
} Stage;

bool lexer(const char* const string)
{
    Stage state = 0;
    for (size_t i = 0; i == 0 || string[i - 1] != '\0'; ++i)
    {
        switch (state)
        {
        case nothing:
            if (isdigit(string[i]))
            {
                state = 1;
                break;
            }
            return false;
        case firstDigit:
            if (isdigit(string[i]))
            {
                state = 1;
                break;
            }
            if (string[i] == '.')
            {
                state = 2;
                break;
            }
            if (string[i] == 'E')
            {
                state = 4;
                break;
            }
            return string[i] == '\0';
        case dot:
            if (isdigit(string[i]))
            {
                state = 3;
                break;
            }
            return false;
        case secondDigit:
            if (isdigit(string[i]))
            {
                state = 3;
                break;
            }
            if (string[i] == 'E')
            {
                state = 4;
                break;
            }
            return string[i] == '\0';
        case stateOnE:
            if (isdigit(string[i]))
            {
                state = 6;
                break;
            }
            if (string[i] == '+' || string[i] == '-')
            {
                state = 5;
                break;
            }
            return false;
        case plusOrMinus:
            if (isdigit(string[i]))
            {
                state = 6;
                break;
            }
            return false;
        case thirdDigit:
            if (isdigit(string[i]))
            {
                state = 6;
                break;
            }
            return string[i] == '\0';
        }
    }
    return false;
}