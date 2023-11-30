#include "sortedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

bool test1(void)
{
    SortedList* sortedList = createSortedList();
    SortedListErrorCode errorCode = ok;
    int checkArray[3] = { 1, 2, 3 };
    add(sortedList, 2);
    add(sortedList, 3);
    add(sortedList, 1);
    bool passed = true;
    for (int i = 0; i < 3; ++i)
    {
        if (front(sortedList, &errorCode) != checkArray[i] || errorCode != ok)
        {
            passed = false;
            break;
        }
        delete(sortedList, checkArray[i]);
    }
    deleteSortedList(&sortedList);
    return passed;
}

bool test2(void)
{
    SortedList* sortedList = createSortedList();
    SortedListErrorCode errorCode = ok;
    int checkArray[3] = { 1, 2, 5 };
    add(sortedList, 2);
    add(sortedList, 3);
    add(sortedList, 1);
    add(sortedList, 5);
    delete(sortedList, 3);
    bool passed = true;
    for (int i = 0; i < 3; ++i)
    {
        if (front(sortedList, &errorCode) != checkArray[i] || errorCode != ok)
        {
            passed = false;
            break;
        }
        delete(sortedList, checkArray[i]);
    }
    deleteSortedList(&sortedList);
    return passed;
}

bool test3(void)
{
    SortedList* sortedList = createSortedList();
    SortedListErrorCode errorCode = ok;
    int checkArray[3] = { 2, 2, 5 };
    add(sortedList, 2);
    add(sortedList, 3);
    add(sortedList, 1);
    add(sortedList, 5);
    delete(sortedList, 3);
    add(sortedList, 2);
    delete(sortedList, 1);
    bool passed = true;
    for (int i = 0; i < 3; ++i)
    {
        if (front(sortedList, &errorCode) != checkArray[i] || errorCode != ok)
        {
            passed = false;
            break;
        }
        delete(sortedList, checkArray[i]);
    }
    return passed;
}

bool test(void)
{
    bool testCases[3] = { test1(), test2(), test3()};
    bool completeTests = true;
    for (int i = 0; i < 3; ++i)
    {
        if (!testCases[i])
        {
            printf("Программа не работает с тестовым случаем %d\n", i + 1);
            completeTests = false;
        }
    }
    return completeTests;
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
        return -1;
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
            errorCode = add(sortedList, value);
        }
        else if (functionNumber == 2)
        {
            printf("Введите число для удаления из сортированного списка: ");
            scanf_s("%d", &value);
            errorCode = delete(sortedList, value);
        }
        else
        {
            printf("На данный момент список имеет такой вид:\n");
            printSortedList(sortedList);
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
