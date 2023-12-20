#include <stdio.h>

#include "PriorityQueue.h"
#include "Test.h"

#define TEST_DID_NOT_PASSED -1234567
#define OK 0

int main()
{
    if (!test())
    {
        return TEST_DID_NOT_PASSED;
    }
    PriorityQueue* queue = createPriorityQueue();
    enqueue(queue, 1, 2);
    enqueue(queue, 1, 3);
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    printf("%d\n", dequeue(queue));
    deletePriorityQueue(&queue);
    return OK;
}
