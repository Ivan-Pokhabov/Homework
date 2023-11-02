#include "CycleList.h"

#include <stdio.h>
#include <locale.h>

bool test(void)
{
    bool testCases[3] = { true, true, true };
    CycleListErrorCode errorCode = ok;
    CycleList* cycleList = createCycleList();
    for (int i = 0; i < 5; ++i)
    {
        CycleListErrorCode addingError = add(&cycleList, i + 1, i + 1);
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
    delete(&cycleList, 3);
    delete(&cycleList, 15);
    int checkArray[3] = { 1, 2, 5 };
    for (int i = 0; i < 3; ++i)
    {
        const int checkValue = get(cycleList, i + 1, &errorCode);
        if (errorCode != ok || checkValue != checkArray[i])
        {
            printf("%d %d", checkValue, checkArray[i]);
            testCases[0] = false;
            break;
        }
    }
    errorCode = ok;
    deleteCycleList(&cycleList);
    cycleList = createCycleList();
    for (int i = 0; i < 5; ++i)
    {
        CycleListErrorCode addingError = add(&cycleList, i + 1, i + 1);
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
    if (deletingByStepExceptLast(&cycleList, 3) != ok)
    {
        printf("Передача нулевого указателя.");
        return false;
    }
    const int lastWarrior = get(cycleList, 1, &errorCode);
    if (errorCode != ok || lastWarrior != 4)
    {
        testCases[1] = false;
    }
    errorCode = ok;
    deleteCycleList(&cycleList);
    cycleList = createCycleList();
    add(&cycleList, 1, 2);
    add(&cycleList, 3, 1);
    delete(&cycleList, 1);
    CycleListErrorCode errorCode1 = ok;
    int elementsCount = elementsNumber(cycleList, &errorCode);
    int number = get(cycleList, 1, &errorCode1);
    if (errorCode != ok || errorCode1 != ok || elementsCount != 1 || number != 1)
    {
        testCases[2] = false;
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
    deleteCycleList(&cycleList);
    return compliteTests;
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
        CycleListErrorCode addingError = add(&cycleList, i + 1, i + 1);
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
