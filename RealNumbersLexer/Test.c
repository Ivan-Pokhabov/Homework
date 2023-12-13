#include <stdbool.h>
#include <stdlib.h>

#include "Test.h"
#include "Lexer.h"

static bool test1(void)
{
    return lexer("12345678900987654321.12345E+12");
}

static bool test2(void)
{
    return lexer("0.1E-1");
}

static bool test3(void)
{
    return lexer("12.12.E-12") == false;
}

bool test(void)
{
    bool tests[3] = { test1(), test2(), test3() };
    bool passed = true;
    for (size_t i = 0; i < 3; ++i)
    {
        if (tests[i] != true)
        {
            passed = false;
            printf("Function does not work with test %lld", i + 1);
        }
    }
    return passed;
}