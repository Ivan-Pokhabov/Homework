#include <stdio.h>
#include <locale.h>

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
    if (scanf_s("%d %d", &number1, &number2) != 2);
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

int main()
{
    setlocale(LC_ALL, "Russian");
    binaryRepresentationTaskSolve();
}
