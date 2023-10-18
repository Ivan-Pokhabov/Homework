#pragma once

//Структура стека, хранящего целые числа.
typedef struct IntStack IntStack;

//Добавлене элемента в начало стека целых чисел. Возвращает -1, если не удалось выделить память под новый элемент стека. Иначе 0.
int pushInt(IntStack** head, int value);

//Удаление эелемента из начала стека целых чисел. Возвращает -1, при передаче пустого стека.
int popInt(IntStack** head);

//Взятие первого элемента стека целых чисел
int topInt(IntStack** head);

//Очистка стека целых чисел
void clearInt(IntStack** head);