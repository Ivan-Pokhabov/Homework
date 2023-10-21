#include "../Stack/IntStack.h"
#include "../Stack/CharStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef enum ErrorCode
{
	ok,
	invalidInput,
	intStackError,
	charStackError
} ErrorCode;

typedef struct
{
	IntStack* numbers;
	CharStack* signs;
} PostfixCalculator;

void arithmeticOperation(PostfixCalculator* calculator, ErrorCode* errorCode, CharStackErrorCode* charStackErrorCode, IntStackErrorCode* intStackErrorCode)
{
	while (calculator->signs != NULL)
	{
		char sign = topChar(&(calculator->signs), charStackErrorCode);
		if (*charStackErrorCode != charOk)
		{
			*errorCode = charStackError;
			return;
		}
		int number1 = topInt(&(calculator->numbers), intStackErrorCode);
		if (*intStackErrorCode != intOk)
		{
			*errorCode = intStackError;
			return;
		}
		popInt(&(calculator->numbers));
		int number2 = topInt(&(calculator->numbers), intStackErrorCode);
		if (*intStackErrorCode != intOk)
		{
			*errorCode = intStackError;
			return;
		}
		popInt(&(calculator->numbers));
		if (sign == '+')
		{
			if (pushInt(&(calculator->numbers), number1 + number2) != intOk)
			{
				*intStackErrorCode = intMemoryError;
				*errorCode = intStackError;
			}
		}
		else if (sign == '*')
		{
			if (pushInt(&(calculator->numbers), number1 * number2) != intOk)
			{
				*intStackErrorCode = intMemoryError;
				*errorCode = intStackError;
			}
		}
		else if (sign == '-')
		{
			if (pushInt(&(calculator->numbers), number1 - number2) != intOk)
			{
				*intStackErrorCode = intMemoryError;
				*errorCode = intStackError;
			}
		}
		else if (sign == '/')
		{
			if (pushInt(&(calculator->numbers), number1 * number2) != intOk)
			{
				*intStackErrorCode = intMemoryError;
				*errorCode = intStackError;
			}
		}
		else
		{
			*errorCode = invalidInput;
			return;
		}
		if (popChar(&(calculator->signs)) != charOk)
		{
			*charStackErrorCode = charNullptr;
			*errorCode = charStackError;
		}
	}
}

int postfixCalculator(FILE* file, ErrorCode* errorCode, CharStackErrorCode* charStackErrorCode, IntStackErrorCode* intStackErrorCode)
{
	PostfixCalculator calculator = { .numbers = NULL, .signs = NULL };
	bool expressionStart = false;
	char symbol = getc(file);
	while (symbol != EOF && symbol != '\n')
	{
		if (symbol == ' ')
		{
			symbol = getc(file);
			continue;
		}
		bool negative = false;
		if (symbol == '-')
		{
			char nextsymbol = getc(file);
			if (nextsymbol == '\n')
			{
				if (pushChar(&(calculator.signs), symbol) != charOk)
				{
					*charStackErrorCode = charMemoryError;
					*errorCode = charStackError;
					clearChar(&(calculator.signs));
					clearInt(&(calculator.numbers));
					return -1;
				}
				break;
			}
			if (nextsymbol >= '0' && nextsymbol <= '9')
			{
				negative = true;
				symbol = nextsymbol;
			}
		}
		if (symbol >= '0' && symbol <= '9')
		{
			if (expressionStart)
			{
				expressionStart = false;
				arithmeticOperation(&calculator, errorCode, charStackErrorCode, intStackErrorCode);
				if (*errorCode != ok || *charStackErrorCode != charOk || *intStackErrorCode != intOk)
				{
					clearChar(&(calculator.signs));
					clearInt(&(calculator.numbers));
					return -1;
				}
			}
			int number = 0;
			while (symbol >= '0' && symbol <= '9')
			{
				number *= 10;
				number += symbol - '0';
				symbol = getc(file);
			}
			if (negative)
			{
				number *= -1;
			}
			if (pushInt(&(calculator.numbers), number) != intOk)
			{
				*intStackErrorCode = intMemoryError;
				*errorCode = intStackError;
				clearChar(&(calculator.signs));
				clearInt(&(calculator.numbers));
				return -1;
			}
		}
		else
		{
			if (pushChar(&(calculator.signs), symbol) != charOk)
			{
				*charStackErrorCode = charMemoryError;
				*errorCode = charStackError;
				clearChar(&(calculator.signs));
				clearInt(&(calculator.numbers));
				return -1;
			}
			expressionStart = true;
		}
		symbol = getc(file);
	}
	arithmeticOperation(&calculator, errorCode, charStackErrorCode, intStackErrorCode);
	if (*errorCode != ok || *charStackErrorCode != charOk || *intStackErrorCode != intOk)
	{
		clearChar(&(calculator.signs));
		clearInt(&(calculator.numbers));
		return -1;
	}
	int result = topInt(&(calculator.numbers), intStackErrorCode);
	if (*intStackErrorCode != intOk)
	{
		*errorCode = intStackError;
	}
	clearChar(&(calculator.signs));
	clearInt(&(calculator.numbers));
	return result;
}

int main()
{	
	setlocale(LC_ALL, "Russian");
	ErrorCode errorCode = ok;
	CharStackErrorCode charStackErrorCode = charOk;
	IntStackErrorCode intStackErrorCode = intOk;
	printf("Введите числовое выражение в постфиксной форме: ");
	int result = postfixCalculator(stdin, &errorCode, &charStackErrorCode, &intStackErrorCode);
	if (errorCode == ok)
	{
		printf("Результат вычислений: %d", result);
	}
	else if (errorCode == charStackError)
	{
		if (charStackErrorCode == charNullptr)
		{
			printf("Некорректное выражение");
		}
		else
		{
			printf("Ошибка выделения памяти");
		}
	}
	else if (errorCode == intStackError)
	{
		if (intStackErrorCode == intNullptr)
		{
			printf("Некорректное выражение");
		}
		else
		{
			printf("Ошибка выделения памяти");
		}
	}
	else
	{
		printf("В выражении присутствуют символы, которые не являются символами калькулятора");
	}
}
