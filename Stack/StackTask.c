#include "CharStack.h"
#include "IntStack.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    IntStack* headInt = NULL;
    pushInt(&headInt, 2);
    IntStackErrorCode intErrorCode = intOk;
    printf("%d\n", topInt(&headInt, &intErrorCode));
    pushInt(&headInt, 2);
    printf("%d\n", topInt(&headInt, &intErrorCode));
    popInt(&headInt);
    printf("%d\n", topInt(&headInt, &intErrorCode));
    pushInt(&headInt, 5);
    printf("%d\n", topInt(&headInt, &intErrorCode));
    pushInt(&headInt, 6);
    printf("%d\n", topInt(&headInt, &intErrorCode));
    pushInt(&headInt, 7);
    printf("%d\n", topInt(&headInt, &intErrorCode));
    popInt(&headInt);
    printf("%d\n", topInt(&headInt, &intErrorCode));
    popInt(&headInt);
    printf("%d\n", topInt(&headInt, &intErrorCode));
    printf("! %d\n", intErrorCode);
    CharStack* headChar = NULL;
    pushChar(&headChar, '+');
    CharStackErrorCode charErrorCode = charOk;
    printf("%c\n", topChar(&headChar, &charErrorCode));
    pushChar(&headChar, '-');
    printf("%c\n", topChar(&headChar, &charErrorCode));
    popChar(&headChar);
    printf("%c\n", topChar(&headChar, &charErrorCode));
    printf("! %d\n", charErrorCode);
    clearChar(&headChar);
    clearInt(&headInt);
}
