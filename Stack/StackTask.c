﻿#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Stack* head = NULL;
    push(&head, 2);
    printf("%d\n", top(head));
    push(&head, 3);
    printf("%d\n", top(head));
    pop(&head);
    printf("%d\n", top(head));
    printf("%d", clear(&head));
}
