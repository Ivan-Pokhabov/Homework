#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

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

void addition(int number1[32], int number2[32], int sum[32])
{
    int oneTransfer = 0;
    for (int i = 31; i > -1; --i)
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

void numberBinaryReference(int number, int binaryNumber[32])
{
    int bit = 0b1;
    for (int i = 31; i > -1; --i)
    {
        if (number & bit)
        {
            binaryNumber[i] = 1;
        }
        bit = bit << 1;
    }
}

void numberDecimalReference(int *number, int binaryNumber[32])
{
    if (binaryNumber[0] == 1)
    {
        int one[32] = { 0 };
        one[31] = 1;
        for (int i = 31; i > 0; --i)
        {
            binaryNumber[i] ^= 1;
        }
        addition(one, binaryNumber, binaryNumber);
    }
    for (int i = 31; i > 0; --i)
    {
        if (binaryNumber[i] == 1)
        {
            *number += 1 << (31 - i);
        }
    }
    if (binaryNumber[0] == 1)
    {
        *number *= -1;
    }
}

void binaryRepresentationTaskSolve(void)
{
    const int number1 = 0;
    const int number2 = 0;
    if (scanf_s("%d %d", &number1, &number2) != 2)
    {
        printf("Вы ввели некорректные данные, пожалуйста, попробуйте снова.");
        return;
    }
    int binaryNumber1[32] = { 0 };
    int binaryNumber2[32] = { 0 };
    numberBinaryReference(number1, binaryNumber1);
    numberBinaryReference(number2, binaryNumber2);
    printBinaryNumber(binaryNumber1, 32);
    printBinaryNumber(binaryNumber2, 32);
    int binarySum[32] = { 0 };
    addition(binaryNumber1, binaryNumber2, binarySum);
    printBinaryNumber(binarySum, 32);
    int sum = 0;
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
    int binaryNumber[32] = { 0 };
    int check[32] = { 0 };
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, 32))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    number = -1;
    for (int i = 0; i < 32; ++i)
    {
        check[i] = 1;
    }
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, 32))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    for (int i = 0; i < 32; ++i)
    {
        binaryNumber[i] = 0;
    }
    number = 2147483647;
    check[0] = 0;
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, 32))
    {
        printBinaryNumber(binaryNumber, 32);
        printBinaryNumber(check, 32);
        printf("\nФункция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    number = -2147483647;
    check[0] = 1;
    for (int i = 1; i > 31; ++i)
    {
        check[i] = 0;
    }
    numberBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, 32))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    return true;
}

bool numberDecimalReferenceTest(void)
{
    int binaryNumber1[32] = { 0 };
    int binaryNumber2[32] = { 0 };
    int binaryNumber3[32] = { 0 };
    int binaryNumber4[32] = { 0 };
    binaryNumber2[0] = 1;
    binaryNumber2[31] = 1;
    for (int i = 0; i < 32; ++i)
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
    if (checkNumber != -2147483647)
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
    if (checkNumber != 2147483647)
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    numberBinaryReferenceTest();
    numberDecimalReferenceTest();
    binaryRepresentationTaskSolve();
}
