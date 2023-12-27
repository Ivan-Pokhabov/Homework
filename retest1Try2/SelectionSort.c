#include <stdlib.h>

#include "SelectionSort.h"

void selectionSort(int array[10])
{
    for (size_t i = 0; i < 9; ++i)
    {
        size_t indexOfMin = i;
        for (size_t j = i + 1; j < 10; ++j)
        {
            if (array[indexOfMin] > array[j])
            {
                indexOfMin = j;
            }
        }
        int temp = array[i];
        array[i] = array[indexOfMin];
        array[indexOfMin] = temp;
    }
}