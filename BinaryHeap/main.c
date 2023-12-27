#include <stdio.h>
#include <stdlib.h>

#include "BinaryHeap.h"

int main()
{
    int array[5] = { 3, 1, 2, 4, 5 };
    int array2[5] = { 2, 4, 3, 1, 0 };
    BinaryHeap* heap = createHeap();
    build(heap, array, array2, 5);
    int key = 0;
    int value = 0;
    pop(heap, &key, &value);
    printf("%d - %d\n", key, value);
    pop(heap, &key, &value);
    printf("%d - %d\n", key, value);
    add(heap, 1, 1);
    pop(heap, &key, &value);
    printf("%d - %d\n", key, value);
    pop(heap, &key, &value);
    printf("%d - %d\n", key, value);
    deleteHeap(&heap);
}
