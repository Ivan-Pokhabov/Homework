#include "Phonebook.h"
#include "Test.h"

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void phonebookSort(char* fileName)
{
    Phonebook* phonebook = createPhonebook();
    PhonebookErrorCode errorCode = ok;
    size_t size = 0;
    if (getFileData(fileName, phonebook, &size) != ok)
    {
        printf("Ошибка чтения из файла");
    }
    instructions();
    int command = -1;
    while (command != 0)
    {
        if (scanf_s("%d", &command) != 1 || command > 3 || command < 0)
        {
            printf("Вы ввели некорректное значение.");
            break;
        }
        if (command == 0)
        {
            return;
        }
        else if (command == 1)
        {
            printf("Введите 1, если хотите отсортировать по имени, 2 - если по номеру: ");
            int parameter = 0;
            if (scanf_s("%d", &parameter) != 1 || parameter != 1 && parameter != 2)
            {
                printf("Вы ввели некорректное значение.");
                break;
            }
            mergeSort(phonebook, 0, size, parameter, &errorCode);
            if (errorCode != ok)
            {
                printf("Программа работает некорректно");
            }
        }
        else
        {
            if (print(phonebook) != ok)
            {
                printf("Ошибка вывода");
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    if (!test())
    {
        return -1;
    }
    phonebookSort("database.txt");
}