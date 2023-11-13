#include "sortedList.h"

#include <stdlib.h>

int main()
{
    SortedList* sortedList = createSortedList();
    add(sortedList, 1);
    add(sortedList, 4);
    add(sortedList, 3);
    add(sortedList, 2);
    printSortedList(sortedList);
    delete(sortedList, 5);
    printSortedList(sortedList);
    delete(sortedList, 1);
    printSortedList(sortedList);
    delete(sortedList, 3);
    printSortedList(sortedList);
    delete(sortedList, 4);
    printSortedList(sortedList);
}
