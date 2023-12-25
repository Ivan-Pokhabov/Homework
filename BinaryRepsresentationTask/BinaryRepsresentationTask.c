#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define BINARY_NUMBER_SIZE (8 * sizeof(int))

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

void addition(int number1[BINARY_NUMBER_SIZE], int number2[BINARY_NUMBER_SIZE], int sum[BINARY_NUMBER_SIZE])
{
    int oneTransfer = 0;
    for (int i = BINARY_NUMBER_SIZE - 1; i > -1; --i)
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

void convertToBinaryReference(int number, int binaryNumber[BINARY_NUMBER_SIZE])
{
    int bit = 0b1;
    for (int i = BINARY_NUMBER_SIZE - 1; i > -1; --i)
    {
        binaryNumber[i] = 0;
        if (number & bit)
        {
            binaryNumber[i] = 1;
        }
        bit = bit << 1;
    }
}

void convertToDecimalReference(int *number, int binaryNumber[BINARY_NUMBER_SIZE])
{
    for (int i = BINARY_NUMBER_SIZE - 1; i > -1; --i)
    {
        if (binaryNumber[i] == 1)
        {
            *number += 1 << (BINARY_NUMBER_SIZE - 1 - i);
        }
    }
}

void binaryRepresentationTaskSolve(const int number1, const int number2)
{
    int binaryNumber1[BINARY_NUMBER_SIZE] = { 0 };
    int binaryNumber2[BINARY_NUMBER_SIZE] = { 0 };
    convertToBinaryReference(number1, binaryNumber1);
    convertToBinaryReference(number2, binaryNumber2);
    printf("Представление числа %d в дополнительном коде : ", number1);
    printBinaryNumber(binaryNumber1, BINARY_NUMBER_SIZE);
    printf("Представление числа %d в дополнительном коде : ", number2);
    printBinaryNumber(binaryNumber2, BINARY_NUMBER_SIZE);
    int binarySum[BINARY_NUMBER_SIZE] = { 0 };
    addition(binaryNumber1, binaryNumber2, binarySum);
    printf("Представление суммы чисел в дополнительном коде : ");
    printBinaryNumber(binarySum, BINARY_NUMBER_SIZE);
    int sum = 0;
    printf("Представление суммы чисел в 10-тичной записи : ");
    convertToDecimalReference(&sum, binarySum);
    printf("%d", sum);
}

bool checkArraysEqual(int array1[], int array2[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (array1[i] != array2[i])
        {
            printf("%d - %d __ %d", array1[i], array2[i], i);
            return false;
        }
    }
    return true;
}

bool numberBinaryReferenceTest(void)
{
    int number = 0;
    int binaryNumber[BINARY_NUMBER_SIZE] = { 0 };
    int check[BINARY_NUMBER_SIZE] = { 0 };
    convertToBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    number = -1;
    for (int i = 0; i < BINARY_NUMBER_SIZE; ++i)
    {
        check[i] = 1;
    }
    convertToBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    for (int i = 0; i < BINARY_NUMBER_SIZE; ++i)
    {
        binaryNumber[i] = 0;
    }
    number = ((1 << (BINARY_NUMBER_SIZE - 1)) - 1);
    check[0] = 0;
    convertToBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, BINARY_NUMBER_SIZE))
    {
        printBinaryNumber(binaryNumber, BINARY_NUMBER_SIZE);
        printBinaryNumber(check, BINARY_NUMBER_SIZE);
        printf("\nФункция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    number = -((1 << (BINARY_NUMBER_SIZE - 1)) - 1);
    check[0] = 1;
    for (int i = 1; i < BINARY_NUMBER_SIZE - 1; ++i)
    {
        check[i] = 0;
    }
    convertToBinaryReference(number, binaryNumber);
    if (!checkArraysEqual(binaryNumber, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция перевода в 2сс не работает с числом %d", number);
        return false;
    }
    return true;
}

bool numberDecimalReferenceTest(void)
{
    int binaryNumber1[BINARY_NUMBER_SIZE] = { 0 };
    int binaryNumber2[BINARY_NUMBER_SIZE] = { 0 };
    int binaryNumber3[BINARY_NUMBER_SIZE] = { 0 };
    int binaryNumber4[BINARY_NUMBER_SIZE] = { 0 };
    binaryNumber2[0] = 1;
    binaryNumber2[BINARY_NUMBER_SIZE - 1] = 1;
    for (int i = 0; i < BINARY_NUMBER_SIZE; ++i)
    {
        binaryNumber3[i] = 1;
        if (i != 0)
        {
            binaryNumber4[i] = 1;
        }
    }
    int checkNumber = 0;
    convertToDecimalReference(&checkNumber, binaryNumber1);
    if (checkNumber != 0)
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    checkNumber = 0;
    convertToDecimalReference(&checkNumber, binaryNumber2);
    if (checkNumber != -((1 << (BINARY_NUMBER_SIZE - 1)) - 1))
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    checkNumber = 0;
    convertToDecimalReference(&checkNumber, binaryNumber3);
    if (checkNumber != -1)
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    checkNumber = 0;
    convertToDecimalReference(&checkNumber, binaryNumber4);
    if (checkNumber != ((1 << (BINARY_NUMBER_SIZE - 1)) - 1))
    {
        printf("Перевод в 10 сс не работает с бинарным представлением числа: %d", checkNumber);
        return false;
    }
    return true;
}

bool additionTest(void)
{
    int binaryNumber1[BINARY_NUMBER_SIZE] = { 0 };
    int binaryNumber2[BINARY_NUMBER_SIZE] = { 0 };
    int binarySum[BINARY_NUMBER_SIZE] = { 0 };
    int check[BINARY_NUMBER_SIZE] = { 0 };
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, BINARY_NUMBER_SIZE);
        printBinaryNumber(binaryNumber2, BINARY_NUMBER_SIZE);
        return false;
    }
    for (int i = 0; i < BINARY_NUMBER_SIZE; ++i)
    {
        binaryNumber1[i] = 1;
    }
    binaryNumber2[BINARY_NUMBER_SIZE - 1] = 1;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, BINARY_NUMBER_SIZE);
        printBinaryNumber(binaryNumber2, BINARY_NUMBER_SIZE);
        return false;
    }
    binaryNumber2[BINARY_NUMBER_SIZE - 3] = 1;
    check[BINARY_NUMBER_SIZE - 3] = 1;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, BINARY_NUMBER_SIZE);
        printBinaryNumber(binaryNumber2, BINARY_NUMBER_SIZE);
        return false;
    }
    for (int i = 0; i < BINARY_NUMBER_SIZE; ++i)
    {
        binaryNumber1[i] = 1;
        binaryNumber2[i] = 1;
        binarySum[i] = 0;
        check[i] ^= 1;
    }
    check[BINARY_NUMBER_SIZE - 1] = 0;
    binaryNumber2[BINARY_NUMBER_SIZE - 3] = 0;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, BINARY_NUMBER_SIZE);
        printBinaryNumber(binaryNumber2, BINARY_NUMBER_SIZE);
        return false;
    }
    for (int i = 0; i < BINARY_NUMBER_SIZE; ++i)
    {
        binarySum[i] = 0;
        check[i] = 0;
        binaryNumber1[i] = 0;
        binaryNumber2[i] = 0;
    }
    binaryNumber2[BINARY_NUMBER_SIZE - 3] = 1;
    binaryNumber1[BINARY_NUMBER_SIZE - 3] = 1;
    binaryNumber1[BINARY_NUMBER_SIZE - 1] = 1;
    check[BINARY_NUMBER_SIZE - 4] = 1;
    check[BINARY_NUMBER_SIZE - 1] = 1;
    addition(binaryNumber1, binaryNumber2, binarySum);
    if (!checkArraysEqual(binarySum, check, BINARY_NUMBER_SIZE))
    {
        printf("Функция прибавления не работает для бинарных чисел: \n");
        printBinaryNumber(binaryNumber1, BINARY_NUMBER_SIZE);
        printBinaryNumber(binaryNumber2, BINARY_NUMBER_SIZE);
        return false;
    }
    return true;
}

bool test(void)
{
    return numberBinaryReferenceTest() && numberDecimalReferenceTest() && additionTest();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    if (!test())
    {
        return -1;
    }
    int number1 = 0;
    int number2 = 0;
    printf("Введите 2 числа, сумма которых по модулю не превышает %d : ", (1 << (BINARY_NUMBER_SIZE - 1)) - 1);
    if (scanf_s("%d %d", &number1, &number2) != 2)
    {
        printf("Вы ввели некорректные входные данные.");
        return 0;
    }
    binaryRepresentationTaskSolve(number1, number2);
}
