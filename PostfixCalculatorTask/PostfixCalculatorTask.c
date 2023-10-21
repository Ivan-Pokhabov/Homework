#include "../Stack/IntStack.h"
#include "../Stack/CharStack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct
{
	IntStack* numbers;
	CharStack* signs;
} PostfixCalculator;

void func(PostfixCalculator* calculator)
{
	while (calculator->signs != NULL)
	{
		char sign = topChar(&(calculator->signs));
		int number1 = topInt(&(calculator->numbers));
		popInt(&(calculator->numbers));
		int number2 = topInt(&(calculator->numbers));
		popInt(&(calculator->numbers));
		if (sign == '+')
		{
			pushInt(&(calculator->numbers), number1 + number2);
		}
		else if (sign == '*')
		{
			pushInt(&(calculator->numbers), number1 * number2);
		}
		else if (sign == '-')
		{
			pushInt(&(calculator->numbers), number1 - number2);
		}
		else if (sign == '/')
		{
			pushInt(&(calculator->numbers), number1 / number2);
		}
		popChar(&(calculator->signs));
	}
}

int postfixCalculator(FILE* file)
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
				pushChar(&(calculator.signs), symbol);
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
				func(&calculator);
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
			pushInt(&(calculator.numbers), number);
		}
		else
		{
			pushChar(&(calculator.signs), symbol);
			expressionStart = true;
		}
		symbol = getc(file);
	}
	func(&calculator);
	int result = topInt(&(calculator.numbers));
	clearChar(&(calculator.signs));
	clearInt(&(calculator.numbers));
	return result;
}

int main()
{	
	setlocale(LC_ALL, "Russian");
	printf("Введите числовое выражение в постфиксной форме: ");
	printf("Результат: %d", postfixCalculator(stdin));
}
