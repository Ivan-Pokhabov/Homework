#include "CycleList.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

CycleListErrorCode deletingByStepExceptLast(CycleList** cycleList, const size_t step)
{
    CycleListErrorCode errorCode = ok;
    CycleListElement* current = getListElement(*cycleList, 0, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }
    while (current != next(current, &errorCode))
    {
        if (delete(cycleList, &current, step) != ok || errorCode != ok)
        {
            return errorCode;
        }
    }
    return ok;
}

bool test1(void)
{
    CycleListErrorCode errorCode = ok;
    CycleList* cycleList = createCycleList();
    for (int i = 0; i < 5; ++i)
    {
        CycleListErrorCode addingError = add(cycleList, i + 1, i + 1);
        if (addingError != ok)
        {
            if (addingError == memoryError)
            {
                printf("Ошибка выделения памяти.");
            }
            else
            {
                printf("Передача нулевого указателя.");
            }
            deleteCycleList(&cycleList);
            return false;
        }
    }
    CycleListElement* element = getListElement(cycleList, 1, &errorCode);
    delete(&cycleList, &element, 3);
    element = getListElement(cycleList, 15, &errorCode);
    delete(&cycleList, &element, 1);
    int checkArray[3] = { 1, 2, 5 };
    bool passed = true;
    for (int i = 0; i < 3; ++i)
    {
        const int checkValue = get(cycleList, i + 1, &errorCode);
        if (errorCode != ok || checkValue != checkArray[i])
        {
            printf("%d %d", checkValue, checkArray[i]);
            passed = false;
            break;
        }
    }
    deleteCycleList(&cycleList);
    return passed;
}

bool test2(void)
{
    CycleListErrorCode errorCode = ok;
    CycleList* cycleList = createCycleList();
    for (int i = 0; i < 5; ++i)
    {
        CycleListErrorCode addingError = add(cycleList, i + 1, i + 1);
        if (addingError != ok)
        {
            if (addingError == memoryError)
            {
                printf("Ошибка выделения памяти.");
            }
            else
            {
                printf("Передача нулевого указателя.");
            }
            deleteCycleList(&cycleList);
            return false;
        }
    }
    CycleListElement* element = getListElement(cycleList, 1, &errorCode);
    if (deletingByStepExceptLast(&cycleList, 3) != ok)
    {
        printf("Передача нулевого указателя.");
        deleteCycleList(&cycleList);
        return false;
    }
    const int lastWarrior = get(cycleList, 1, &errorCode);
    bool passed = true;
    if (errorCode != ok || lastWarrior != 4)
    {
        passed = false;
        printf("%d", lastWarrior);
    }
    deleteCycleList(&cycleList);
    return passed;
}

bool test3()
{
    CycleListErrorCode errorCode = ok;
    CycleList* cycleList = createCycleList();
    add(cycleList, 1, 2);
    add(cycleList, 3, 1);
    CycleListElement* element = getListElement(cycleList, 1, &errorCode);
    delete(&cycleList, &element, 1);
    CycleListErrorCode errorCode1 = ok;
    int number = get(cycleList, 1, &errorCode1);
    deleteCycleList(&cycleList);
    if (errorCode != ok || errorCode1 != ok || number != 1)
    {
        return false;
    }
    return true;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    if (!test())
    {
        return -1;
    }
    CycleListErrorCode errorCode = ok;
    CycleList* cycleList = createCycleList();
    int warriorsNumber = 0;
    int murderedNumber = 0;
    printf("Введите n и m: ");
    if (scanf_s("%d %d", &warriorsNumber, &murderedNumber) != 2 || murderedNumber <= 0 || warriorsNumber <= 0)
    {
        printf("Вы ввели некорректное значение.");
        return -1;
    }
    for (int i = 0; i < warriorsNumber; ++i)
    {
        CycleListErrorCode addingError = add(cycleList, i + 1, i + 1);
        if (addingError != ok)
        {
            if (addingError == memoryError)
            {
                printf("Ошибка выделения памяти.");
            }
            else
            {
                printf("Передача нулевого указателя.");
            }
            return false;
        }
    }
    if (deletingByStepExceptLast(&cycleList, murderedNumber) != ok)
    {
        printf("Программа работает неверно.");
        return -3;
    }
    const int lastWarrior = get(cycleList, 1, &errorCode);
    if (errorCode != ok)
    {
        printf("Программа работает неверно.");
        return -3;
    }
    printf("Последний воин в начале будет на %d позиции", lastWarrior);
    deleteCycleList(&cycleList);
}
