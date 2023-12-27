#include <stdio.h>
#include <stdbool.h>

#include "Lexer.h"
#include "Test.h"

#define TEST_DID_NOT_PASSED -1
#define OK 0

int main()
{
    if (!test())
    {
        return TEST_DID_NOT_PASSED;
    }
    if (lexer("1.2E+3"))
    {
        printf("YES");
    }
    return OK;
}
