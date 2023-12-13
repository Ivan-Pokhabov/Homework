#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "Lexer.h"

bool lexer(const char* const string)
{
    int state = 0;
    for (size_t i = 0; i == 0 || string[i - 1] != '\0'; ++i)
    {
        switch (state)
        {
        case 0:
            if (isdigit(string[i]))
            {
                state = 1;
                break;
            }
            return false;
        case 1:
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
        case 2:
            if (isdigit(string[i]))
            {
                state = 3;
                break;
            }
            return false;
        case 3:
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
        case 4:
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
        case 5:
            if (isdigit(string[i]))
            {
                state = 6;
                break;
            }
            return false;
        case 6:
            if (isdigit(string[i]))
            {
                state = 6;
                break;
            }
            return string[i] == '\0';
        }
    }
}