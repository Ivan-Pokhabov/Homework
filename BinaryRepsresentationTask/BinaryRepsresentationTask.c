#include <stdio.h>

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
        //printf("!");
       // printBinaryNumber(binaryNumber, 32);
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

int main()
{
    int num1 = -5;
    int num2 = -3;
    int num3 = 0;
    int num4 = 0;
    int number1[32] = { 0 };
    int number2[32] = { 0 };
    numberBinaryReference(num1, number1);
    numberBinaryReference(num2, number2);
    printBinaryNumber(number1, 32);
    printBinaryNumber(number2, 32);
    int sum[32] = { 0 };
    addition(number1, number2, sum);
    printBinaryNumber(sum, 32);
    numberDecimalReference(&num3, number1);
    numberDecimalReference(&num4, number2);
    int num = 0;
    numberDecimalReference(&num, sum);
    printf("%d\n%d\n%d", num3, num4, num);
}
