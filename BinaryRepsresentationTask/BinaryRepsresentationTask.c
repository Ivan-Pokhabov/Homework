#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define binaryNumberSize 8 * sizeof(int)

void printBinaryNumber(int array[], const int arrayLength)
{
    if (arrayLength == 0)
    {
        printf("None\n");
        return;
    }
    for (int i = 0; i < arrayLength; i++)
    {
        printf("%d", array[i]);
    }
    printf("\n");
}

void addition(int number1[binaryNumberSize], int number2[binaryNumberSize], int sum[binaryNumberSize])
{
    int oneTransfer = 0;
    for (int i = binaryNumberSize - 1; i > -1; --i)
    {
        sum[i] = oneTransfer + number1[i] + number2[i];
        oneTransfer = 0;
        if (sum[i] > 1)
        {
            sum[i] -= 2;
            oneTransfer = 1;
        }
    }
}

void numberBinaryReference(int number, int binaryNumber[binaryNumberSize])
{
    int bit = 0b1;
    for (int i = binaryNumberSize - 1; i > -1; --i)
    {
        if (number & bit)
        {
            binaryNumber[i] = 1;
        }
        bit = bit << 1;
    }
}

void numberDecimalReference(int *number, int binaryNumber[binaryNumberSize])
{
    if (binaryNumber[0] == 1)
    {
        int one[binaryNumberSize] = { 0 };
        one[binaryNumberSize - 1] = 1;
        for (int i = binaryNumberSize - 1; i > 0; --i)
        {
            binaryNumber[i] ^= 1;
        }
        addition(one, binaryNumber, binaryNumber);
    }
    for (int i = binaryNumberSize - 1; i > 0; --i)
    {
        if (binaryNumber[i] == 1)
        {
            *number += 1 << (binaryNumberSize - 1 - i);
        }
    }
    if (binaryNumber[0] == 1)
    {
        *number *= -1;
    }
}

void binaryRepresentationTaskSolve(void)
{
    printf("Введите 2 числа сумма, которых не превышает число %d по модулю : ", (1 << (binaryNumberSize - 1)) - 1);
    const int number1 = 0;
    const int number2 = 0;
    if (scanf_s("%d %d", &number1, &number2) != 2)
    {
        printf("Вы ввели некорректные данные, пожалуйста, попробуйте снова.");
        return;
    }
    int binaryNumber1[binaryNumberSize] = { 0 };
    int binaryNumber2[binaryNumberSize] = { 0 };
    numberBinaryReference(number1, binaryNumber1);
    numberBinaryReference(number2, binaryNumber2);
    printf("Представление числа %d в дополнительном коде : ", number1);
    printBinaryNumber(binaryNumber1, binaryNumberSize);
    printf("Представление числа %d в дополнительном коде : ", number2);
    printBinaryNumber(binaryNumber2, binaryNumberSize);
    int binarySum[binaryNumberSize] = { 0 };
    addition(binaryNumber1, binaryNumber2, binarySum);
    printf("Представление суммы чисел в дополнительном коде : ");
    printBinaryNumber(binarySum, binaryNumberSize);
    int sum = 0;
    printf("Представление суммы чисел в 10-тичной записи : ");
    numberDecimalReference(&sum, binarySum);
    printf("%d", sum);
}
bool checkArraysEqual(int array1[], int array2[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool numberBinaryReferenceTest(void)
{
    int number = 0;
    int binaryNumber[binaryNumberSize] = { 0 };
    int check[binaryNumberSize] = { 0 };
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, binaryNumberSize))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    number = -1;
    for (int i = 0; i < binaryNumberSize; ++i)
    {
        check[i] = 1;
    }
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, binaryNumberSize))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    for (int i = 0; i < binaryNumberSize; ++i)
    {
        binaryNumber[i] = 0;
    }
    number = ((1 << (binaryNumberSize - 1)) - 1);
    check[0] = 0;
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, binaryNumberSize))
    {
        printBinaryNumber(binaryNumber, binaryNumberSize);
        printBinaryNumber(check, binaryNumberSize);
        printf("\nФункция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    number = -((1 << (binaryNumberSize - 1)) - 1);
    check[0] = 1;
    for (int i = 1; i > binaryNumberSize - 1; ++i)
    {
        check[i] = 0;
    }
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, binaryNumberSize))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    return true;
}

bool numberDecimalReferenceTest(void)
{
    int binaryNumber1[binaryNumberSize] = { 0 };
    int binaryNumber2[binaryNumberSize] = { 0 };
    int binaryNumber3[binaryNumberSize] = { 0 };
    int binaryNumber4[binaryNumberSize] = { 0 };
    binaryNumber2[0] = 1;
    binaryNumber2[binaryNumberSize - 1] = 1;
    for (int i = 0; i < binaryNumberSize; ++i)
    {
        binaryNumber3[i] = 1;
        if (i != 0)
        {
            binaryNumber4[i] = 1;
        }
    }
    int checkNumber = 0;
    numberDecimalReference(&checkNumber, binaryNumber1);
    if (checkNumber != 0)
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    checkNumber = 0;
    numberDecimalReference(&checkNumber, binaryNumber2);
    if (checkNumber != -((1 << (binaryNumberSize - 1)) - 1))
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    checkNumber = 0;
    numberDecimalReference(&checkNumber, binaryNumber3);
    if (checkNumber != -1)
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    checkNumber = 0;
    numberDecimalReference(&checkNumber, binaryNumber4);
    if (checkNumber != ((1 << (binaryNumberSize - 1)) - 1))
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    return true;
}

bool additionTest(void)
{
    int binaryNumber1[binaryNumberSize] = { 0 };
    int binaryNumber2[binaryNumberSize] = { 0 };
    int binarySum[binaryNumberSize] = { 0 };
    int check[binaryNumberSize] = { 0 };
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, binaryNumberSize))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, binaryNumberSize);
        printBinaryNumber(binaryNumber2, binaryNumberSize);
        return false;
    }
    for (int i = 0; i < binaryNumberSize; ++i)
    {
        binaryNumber1[i] = 1;
    }
    binaryNumber2[31] = 1;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, binaryNumberSize))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, binaryNumberSize);
        printBinaryNumber(binaryNumber2, binaryNumberSize);
        return false;
    }
    binaryNumber2[29] = 1;
    check[29] = 1;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, binaryNumberSize))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, binaryNumberSize);
        printBinaryNumber(binaryNumber2, binaryNumberSize);
        return false;
    }
    for (int i = 0; i < binaryNumberSize; ++i)
    {
        binaryNumber1[i] = 1;
        binaryNumber2[i] = 1;
        binarySum[i] = 0;
        check[i] ^= 1;
    }
    check[31] = 0;
    binaryNumber2[29] = 0;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, binaryNumberSize))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, binaryNumberSize);
        printBinaryNumber(binaryNumber2, binaryNumberSize);
        return false;
    }
    for (int i = 0; i < binaryNumberSize; ++i)
    {
        binarySum[i] = 0;
        check[i] = 0;
        binaryNumber1[i] = 0;
        binaryNumber2[i] = 0;
    }
    binaryNumber2[29] = 1;
    binaryNumber1[29] = 1;
    binaryNumber1[31] = 1;
    check[28] = 1;
    check[31] = 1;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, binaryNumberSize))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, binaryNumberSize);
        printBinaryNumber(binaryNumber2, binaryNumberSize);
        return false;
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    numberBinaryReferenceTest();
    numberDecimalReferenceTest();
    additionTest();
    binaryRepresentationTaskSolve();
}
