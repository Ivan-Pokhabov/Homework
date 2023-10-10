#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h> 

typedef struct
{
    char name[100];
    char number[100];
} Phonebook;

void add(Phonebook phonebook[], const int currentPosition)
{
    printf("Введите имя: ");
    scanf_s("%s", phonebook[currentPosition].name, _countof(phonebook[currentPosition].name));
    printf("Введите номер телефона: ");
    scanf_s("%s", phonebook[currentPosition].number, _countof(phonebook[currentPosition].number));
}

void print(Phonebook phonebook[], const int currentPosition)
{
    for (int i = 0; i < currentPosition; ++i)
    {
        printf("Имя : %s Номер : %s\n", phonebook[i].name, phonebook[i].number);
    }
}

void findNumber(const char name[], Phonebook phonebook[], const int currentPosition)
{
    for (int i = 0; i < currentPosition; ++i)
    {
        if (strcmp(name, phonebook[i].name) == 0)
        {
            printf("Имя найдено! Телефон : %s\n", phonebook[i].number);
            return;
        }
    }
    printf("Имя не найдено!\n");
}

void findName(const char number[], Phonebook phonebook[], const int currentPosition)
{
    for (int i = 0; i < currentPosition; ++i)
    {
        if (strcmp(number, phonebook[i].number) == 0)
        {
            printf("Телефон найден! Имя : %s\n", phonebook[i].name);
            return;
        }
    }
    printf("Телефон не найден!\n");
}

void getFileData(const char fileName[], Phonebook phonebook[])
{
    
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Phonebook* phonebook[100];
    add(phonebook, 0);
    add(phonebook, 1);
    print(phonebook, 2);
}