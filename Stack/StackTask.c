#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    IntStack* headInt = NULL;
    pushInt(&headInt, 2);
    printf("%d\n", topInt(&headInt));
    pushInt(&headInt, 2);
    printf("%d\n", topInt(&headInt));
    popInt(&headInt);
    printf("%d\n", topInt(&headInt));
    pushInt(&headInt, 5);
    printf("%d\n", topInt(&headInt));
    pushInt(&headInt, 6);
    printf("%d\n", topInt(&headInt));
    pushInt(&headInt, 7);
    printf("%d\n", topInt(&headInt));
    popInt(&headInt);
    printf("%d\n", topInt(&headInt));
    popInt(&headInt);
    printf("%d\n", topInt(&headInt));
    CharStack* headChar = NULL;
    pushChar(&headChar, '+');
    printf("%c\n", topChar(&headChar));
    pushChar(&headChar, '-');
    printf("%c\n", topChar(&headInt));
    popChar(&headChar);
    printf("%c\n", topChar(&headChar));
    clearChar(&headChar);
    clearInt(&headInt);
}
