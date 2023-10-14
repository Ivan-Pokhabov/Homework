#include "Stack.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Stack* head = NULL;
    push(&head, '2');
    printf("%d\n", top(head) - '0');
    push(&head, '3');
    printf("%d\n", top(head) - '0');
    pop(&head);
    printf("%d\n", top(head) - '0');
    printf("%d\n", clear(&head));
    push(&head, '5');
    printf("%d\n", top(head) - '0');
    push(&head, '6');
    printf("%d\n", top(head) - '0');
    push(&head, '7');
    printf("%d\n", top(head) - '0');
    pop(&head);
    printf("%d\n", top(head) - '0');
    pop(&head);
    printf("%d\n", top(head) - '0');
    printf("%d", clear(&head));
}
