#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARRAYLENGTH 100

void zerosElementsTask(void)
{
    int arraySize = 0, zerosCount = 0;
    printf("Enter the number of elements in the array (natural number): ");
    scanf_s("%d", &arraySize);
    for (int i = 0; i < arraySize; i++)
    {
        int number = 0;
        scanf_s("%d", &number);
        if (number == 0)
        {
            zerosCount++;
        }
    }
    printf("The number of zeros in the array is %d", zerosCount);
}

void swapTask(void)
{
    int firstNumber = 0;
    int secondNumber = 0;
    printf("Enter first number: ");
    scanf_s("%d", &firstNumber);
    printf("Enter second number: ");
    scanf_s("%d", &secondNumber);
    firstNumber += secondNumber;
    secondNumber += secondNumber - firstNumber;
    firstNumber = (firstNumber + secondNumber) / 2;
    secondNumber = firstNumber - secondNumber;
    printf("First number is %d \nSecond number is %d", firstNumber, secondNumber);
}

void incompleteQuotientTask(void)
{
    int divisible = 0;
    int divisor = 0;
    printf("Enter divisible : ");
    scanf_s("%d", &divisible);
    printf("Enter divisor : ");
    scanf_s("%d", &divisor);
    if (divisor == 0)
    {
        printf("You cannot be divided by 0");
    }
    else
    {
        int incompleteQuotient = 0;
        int symbol = 1;
        bool negativeDivisible = false;
        if (divisible * divisor < 0)
        {
            symbol *= -1;
        }
        if (divisible < 0)
        {
            divisible *= -1;
            negativeDivisible = true;
        }
        if (divisor < 0)
        {
            divisor *= -1;
        }
        while (divisible > 0)
        {
            divisible -= divisor;
            incompleteQuotient++;
        }
        if (divisible < 0 && ((symbol > 0 && !negativeDivisible) || (symbol < 0 && !negativeDivisible)))
        {
            incompleteQuotient--;
        }
        incompleteQuotient *= symbol;
        printf("Incomplete quotient of division is %d", incompleteQuotient);
    }
}

int findDigitsSum(int number)
{
    int digitsSum = 0;
    while (number > 0)
    {
        digitsSum += number % 10;
        number /= 10;
    }
    return digitsSum;
}

void ticketsTask(void)
{
    int sumsCount[28] = { 0 };
    for (int i = 0; i < 1000; i++)
    {
        sumsCount[findDigitsSum(i)]++;
    }
    int ticketsAmount = 0;
    for (int i = 0; i < 28; i++)
    {
        ticketsAmount += sumsCount[i] * sumsCount[i];
    }
    printf("Amount of lucky tickets is %d", ticketsAmount);
}

void braceBalanceTask(void)
{
    printf("Enter your expression(length should be no more 10^6) : ");
    char expression[1000001];
    scanf_s("%s", expression, 1000000);
    printf("Enter length of your expression : ");
    int expressionLength = 0;
    scanf_s("%d", &expressionLength);
    int stringBalance = 0;
    bool badBalance = false;
    for (int i = 0; i < expressionLength; i++)
    {
        if (expression[i] == '(')
        {
            stringBalance++;
        }
        else
        {
            stringBalance--;
        }
        if (stringBalance < 0)
        {
            badBalance = true;
            break;
        }
    }
    if (badBalance || stringBalance > 0)
    {
        printf("Expresiion is imbalanced");
    }
    else
    {
        printf("Expression is balanced");
    }
}

void primesNumbersTask(void)
{
    printf("Enter number no more 100000 : ");
    int number = 0;
    scanf_s("%d", &number);
    int primesArray[100001] = { 0 };
    for (int i = 2; i <= number; i++)
    {
        if (primesArray[i] == 0)
        {
            for (int j = i * 2; j < 100001; j += i)
            {
                primesArray[j]++;
            }
        }
    }
    for (int i = 2; i <= number; i++)
    {
        if (primesArray[i] == 0)
        {
            printf("%d ", i);
        }
    }
}

void prefixFucntion(const char* string, int prefixArray[], const int stringLength)
{
    for (int i = 1; i < stringLength; i++)
    {
        int currentFuctionValue = prefixArray[i - 1];
        while (string[i] != string[currentFuctionValue] && currentFuctionValue > 0)
        {
            currentFuctionValue--;
        }
        prefixArray[i] = currentFuctionValue;
        if (string[i] == string[currentFuctionValue])
        {
            prefixArray[i]++;
        }
    }
}

void substringTask(void)
{
    printf("Enter first string(length should be no more than 10^4) : ");
    char firstString[10001];
    scanf_s("%s", firstString, 10000);
    const int firstLength = strlen(firstString);
    printf("Enter second string(length should be no more than 10^4) : ");
    char secondString[10001];
    scanf_s("%s", secondString, 10000);
    const int secondLength = strlen(secondString);
    char stringSum[20002];
    snprintf(stringSum, sizeof stringSum, "%s#%s", firstString, secondString);
    int prefixArray[20001] = { 0 };
    int sumLength = firstLength + secondLength + 1;
    prefixFucntion(stringSum, prefixArray, sumLength);
    int substringsNumber = 0;
    for (int i = 0; i < sumLength; i++)
    {
        if (prefixArray[i] == firstLength)
        {
            substringsNumber++;
        }
    }
    printf("Number of substring is %d", substringsNumber);
}

void reversePartOfArray(int start, int end, int array[])
{
    for (int i = start; i < (start + end + 1) / 2; i++)
    {
        const int swap = array[i];
        array[i] = array[end - i + start];
        array[end - i + start] = swap;
    }
}

void arrayOutput(int length, int array[])
{
    printf("New array : ");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
}

void arrayTask(void)
{
    printf("Enter number of first array substract : ");
    int firstSubstractNumber = 0;
    scanf_s("%d", &firstSubstractNumber);
    printf("Enter number of second array substract : ");
    int secondSubstractNumber = 0;
    scanf_s("%d", &secondSubstractNumber);
    printf("Enter array : ");
    int array[10001];
    for (int i = 0; i < firstSubstractNumber + secondSubstractNumber; i++)
    {
        scanf_s("%d", &array[i]);
    }
    reversePartOfArray(0, firstSubstractNumber - 1, array);
    reversePartOfArray(firstSubstractNumber, firstSubstractNumber + secondSubstractNumber - 1, array);
    reversePartOfArray(0, firstSubstractNumber + secondSubstractNumber - 1, array);
    arrayOutput(firstSubstractNumber + secondSubstractNumber, array);
}

int iterativeSearchForFibonacciNumber(const int number)
{
    int currentFibonacciNumber = 0;
    int lastFibonacciNumber = 1;
    int penultimateFibonacciNumber = 1;
    for (int i = 0; i < number - 1; i++)
    {
        penultimateFibonacciNumber = lastFibonacciNumber;
        lastFibonacciNumber = currentFibonacciNumber;
        currentFibonacciNumber = lastFibonacciNumber + penultimateFibonacciNumber;
    }
    return currentFibonacciNumber;
}

int recursiveSearchForFibonacciNumber(const int number)
{
    if (number == 1)
    {
        return 0;
    }
    if (number <= 3)
    {
        return 1;
    }
    return recursiveSearchForFibonacciNumber(number - 1) + recursiveSearchForFibonacciNumber(number - 2);
}

void fibonacciNumbersTask(void)
{
    printf("Enter the number of the Fibonacci number : ");
    int number = 0;
    scanf_s("%d", &number);
    int fibonacciNumber = recursiveSearchForFibonacciNumber(number);
    //int fibonacciNumber = iterativeSearchForFibonacciNumber(number);
    printf("Your number is %d", fibonacciNumber);
    // Рекурсивное вычисление начинает работать заметно медленнее уже при вычислении 40 числа Фибоначчи
}

int binaryExponentiation(const int base, const int degree)
{
    if (degree == 0)
    {
        return 1;
    }
    if (degree % 2 == 1)
    {
        return binaryExponentiation(base, degree - 1) * base;
    }
    int halfDegreeNumber = binaryExponentiation(base, degree / 2);
    return halfDegreeNumber * halfDegreeNumber;
}

int linearExponentiation(const int base, const int degree)
{
    int exponentiationResult = 1;
    for (int i = 0; i < degree; i++)
    {
        exponentiationResult *= base;
    }
    return exponentiationResult;
}

void exponentiationTask(void)
{
    printf("Enter the base of the power function : ");
    int base = 0;
    scanf_s("%d", &base);
    printf("Enter the degree of the power function : ");
    int degree = 0;
    scanf_s("%d", &degree);
    int result = binaryExponentiation(base, degree);
    //int result = linearExponentiation(base, degree);
    printf("Result of exponentiation is %d", result);
}

int main()
{
    zerosElementsTask();
    swapTask();
    incompleteQuotientTask();
    ticketsTask();
    braceBalanceTask();
    primesNumbersTask();
    substringTask();
    arrayTask();
    fibonacciNumbersTask();
    exponentiationTask();
}
