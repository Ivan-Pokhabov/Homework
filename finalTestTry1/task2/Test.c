#include <stdio.h>
#include <stdbool.h>

#include "PriorityQueue.h"
#include "Test.h"

static bool test1(void)
{
    PriorityQueue* queue = createPriorityQueue();
    enqueue(queue, 1, 3);
    enqueue(queue, 1, 2);
    if (dequeue(queue) != 3 || dequeue(queue) != 2 || dequeue(queue) != -1)
    {
        deletePriorityQueue(&queue);
        return false;
    }
    deletePriorityQueue(&queue);
    return true;
}

static bool test2(void)
{
    PriorityQueue* queue = createPriorityQueue();
    if (dequeue(queue) != -1 || dequeue(queue) != -1)
    {
        deletePriorityQueue(&queue);
        return false;
    }
    deletePriorityQueue(&queue);
    return true;
}

static bool test3(void)
{
    PriorityQueue* queue = createPriorityQueue();
    enqueue(queue, 3, 1);
    enqueue(queue, 2, 2);
    enqueue(queue, 1, 3);
    if (dequeue(queue) != 3 || dequeue(queue) != 2 || dequeue(queue) != 1)
    {
        deletePriorityQueue(&queue);
        return false;
    }
    deletePriorityQueue(&queue);
    return true;
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
