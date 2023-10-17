#include "Stack/Stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	PostfixCalculator calculator = { .numbers = NULL, .signs = NULL };
	char symbol = getchar();
	bool expressionStart = false;
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
	printf("%d\n", topInt(&(calculator.numbers)));
	clearChar(&(calculator.signs));
	clearInt(&(calculator.numbers));
}
