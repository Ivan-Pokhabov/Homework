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
    Stage state = nothing;
    for (size_t i = 0; i == 0 || string[i - 1] != '\0'; ++i)
    {
        switch (state)
        {
        case nothing:
            if (isdigit(string[i]))
            {
                state = firstDigit;
                break;
            }
            return false;
        case firstDigit:
            if (isdigit(string[i]))
            {
                state = firstDigit;
                break;
            }
            if (string[i] == '.')
            {
                state = dot;
                break;
            }
            if (string[i] == 'E')
            {
                state = stateOnE;
                break;
            }
            return string[i] == '\0';
        case dot:
            if (isdigit(string[i]))
            {
                state = secondDigit;
                break;
            }
            return false;
        case secondDigit:
            if (isdigit(string[i]))
            {
                state = secondDigit;
                break;
            }
            if (string[i] == 'E')
            {
                state = stateOnE;
                break;
            }
            return string[i] == '\0';
        case stateOnE:
            if (isdigit(string[i]))
            {
                state = thirdDigit;
                break;
            }
            if (string[i] == '+' || string[i] == '-')
            {
                state = plusOrMinus;
                break;
            }
            return false;
        case plusOrMinus:
            if (isdigit(string[i]))
            {
                state = thirdDigit;
                break;
            }
            return false;
        case thirdDigit:
            if (isdigit(string[i]))
            {
                state = thirdDigit;
                break;
            }
            return string[i] == '\0';
        }
    }
    return false;
}