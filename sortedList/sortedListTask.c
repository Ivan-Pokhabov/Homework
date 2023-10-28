#include "sortedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

SortedListErrorCode sortedListFunctions(SortedList** sortedList, const int functionNumber, const int value)
{
    if (functionNumber == 1)
    {
        return add(*sortedList, value);
    }
    else if (functionNumber == 2)
    {
        return delete(*sortedList, value);
    }
    else
    {
        printSortedList(*sortedList);
        return ok;
    }
}

bool test(void)
{
    bool testCases[3] = { true, true, true };
    SortedList* sortedList = createSortedList();
    SortedListErrorCode errorCode = ok;
    int checkArray[3] = { 1, 2, 3 };
    add(sortedList, 2);
    add(sortedList, 3);
    add(sortedList, 1);
    for (int i = 0; i < 3; ++i)
    {
        if (front(sortedList, &errorCode) != checkArray[i] || errorCode != ok)
        {
            testCases[0] = false;
            break;
        }
        delete(sortedList, checkArray[i]);
    }
    deleteSortedList(&sortedList);
    sortedList = createSortedList();
    errorCode = ok;
    checkArray[2] = 5;
    add(sortedList, 2);
    add(sortedList, 3);
    add(sortedList, 1);
    add(sortedList, 5);
    delete(sortedList, 3);
    for (int i = 0; i < 3; ++i)
    {
        if (front(sortedList, &errorCode) != checkArray[i] || errorCode != ok)
        {
            testCases[1] = false;
            break;
        }
        delete(sortedList, checkArray[i]);
    }
    deleteSortedList(&sortedList);
    sortedList = createSortedList();
    errorCode = ok;
    checkArray[0] = 2;
    add(sortedList, 2);
    add(sortedList, 3);
    add(sortedList, 1);
    add(sortedList, 5);
    delete(sortedList, 3);
    add(sortedList, 2);
    delete(sortedList, 1);
    for (int i = 0; i < 3; ++i)
    {
        if (front(sortedList, &errorCode) != checkArray[i] || errorCode != ok)
        {
            testCases[2] = false;
            break;
        }
        delete(sortedList, checkArray[i]);
    }
    bool compliteTests = true;
    for (int i = 0; i < 3; ++i)
    {
        if (!testCases[i])
        {
            printf("Программа не работает с тестовым случаем %d\n", i + 1);
            compliteTests = false;
        }
    }
    return compliteTests;
}

void instructions(void)
{
    printf("Программа имеет такой функционал:\n");
    printf("0 – выйти\n");
    printf("1 – добавить значение в сортированный список\n");
    printf("2 – удалить значение из списка\n");
    printf("3 – распечатать список\n");
}

int main()
{
    setlocale(LC_ALL, "Russian");
    if (!test())
    {
        //return 0;
    }
    instructions();
    SortedList* sortedList = createSortedList();
    printf("Введите номер функции: ");
    int functionNumber = 0;
    scanf_s("%d", &functionNumber);
    while (functionNumber != 0)
    {
        int value = 0;
        SortedListErrorCode errorCode = ok;
        if (functionNumber == 1)
        {
            printf("Введите число для добавления в сортированный список: ");
            scanf_s("%d", &value);
            errorCode = sortedListFunctions(&sortedList, 1, value);
        }
        else if (functionNumber == 2)
        {
            printf("Введите число для удаления из сортированного списка: ");
            scanf_s("%d", &value);
            errorCode = sortedListFunctions(&sortedList, 2, value);
        }
        else
        {
            printf("На данный момент список имеет такой вид:\n");
            sortedListFunctions(&sortedList, 3, -1);
        }
        if (errorCode != ok)
        {
            if (errorCode == nullptr)
            {
                printf("Попытка удаления из пустого списка\n");
            }
            else if (errorCode == memoryError)
            {
                printf("Ошибка выделения памяти\n");
            }
            else
            {
                printf("Попытка удаления элемента, которого нет в списке\n");
            }
            printf("Попробуйте заново\n");
        }
        printf("Введите номер функции: ");
        scanf_s("%d", &functionNumber);
    }
    deleteSortedList(&sortedList);
}
