#include "C:/Repos/Homework/Stack/Stack.h"

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

int main()
{	
	setlocale(LC_ALL, "Russian");
	PostfixCalculator calculator = { .numbers = NULL, .signs = NULL };
	printf("Введите числовое выражение в постфиксной форме: ");
	bool expressionStart = false;
	char symbol = getchar();
	while (symbol != EOF && symbol != '\n')
	{
		if (symbol == ' ')
		{
			symbol = getchar();
			continue;
		}
		bool negative = false;
		if (symbol == '-')
		{
			char nextsymbol = getchar();
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
				symbol = getchar();
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
		symbol = getchar();
	}
	func(&calculator);
	printf("Результат: %d", topInt(&(calculator.numbers)));
	clearChar(&(calculator.signs));
	clearInt(&(calculator.numbers));
}
