#pragma once

//Структура стека, хранящего символы.
typedef struct CharStack CharStack;

//Добавлене элемента в начало стека символов. Возвращает -1, если не удалось выделить память под новый элемент стека. Иначе 0.
int pushChar(CharStack** head, char value);

//Удаление эелемента из начала стека символов. Возвращает -1, при передаче пустого стека.
int popChar(CharStack** head);

//Взятие первого элемента стека символов
char topChar(CharStack** head);

//Очистка стека символов
void clearChar(CharStack** head);
