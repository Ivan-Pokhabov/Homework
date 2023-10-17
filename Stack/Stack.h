#pragma once


//Структура стека, хранящего целые числа.
typedef struct
{
	int value;
	struct IntStack* previous;
} IntStack;

//Структура стека, хранящего символы
typedef struct
{
	char value;
	struct CharStack* previous;
} CharStack;

//Добавлене элемента в начало стека символов. Возвращает -1, если не удалось выделить память под новый элемент стека. Иначе 0.
int pushChar(CharStack** head, char value);

//Добавлене элемента в начало стека целых чисел. Возвращает -1, если не удалось выделить память под новый элемент стека. Иначе 0.
int pushInt(IntStack** head, int value);

//Удаление эелемента из начала стека символов. Возвращает -1, при передаче пустого стека.
int popChar(CharStack** head);

//Удаление эелемента из начала стека целых чисел. Возвращает -1, при передаче пустого стека.
int popInt(IntStack** head);

//Взятие первого элемента стека символов
char topChar(CharStack** head);

//Взятие первого элемента стека целых чисел
int topInt(IntStack** head);

//Очистка стека символов
void clearChar(CharStack** head);

//Очистка стека целых чисел
void clearInt(IntStack** head);