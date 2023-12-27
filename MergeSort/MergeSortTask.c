#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Phonebook.h"
#include "Test.h"

#define INCORRECT_INPUT -10

void instructions(void)
{
    printf("0 - выйти\n");
    printf("1 - отсортировать записи\n");
    printf("2 - распечатать все имеющиеся записи\n");
}

PhonebookErrorCode phonebookSort(const char* const fileName)
{
    Phonebook* phonebook = createPhonebook();
    if (phonebook == NULL)
    {
        return nullptr;
    }
    PhonebookErrorCode errorCode = ok;
    size_t size = 0;
    if (getFileData(fileName, phonebook, &size) != ok)
    {
        return fileOpeningError;
    }
    instructions();
    int command = -1;
    while (command != 0)
    {
        if (scanf_s("%d", &command) != 1 || command > 3 || command < 0)
        {
            deletePhonebook(&phonebook);
            return INCORRECT_INPUT;
        }
        if (command == 0)
        {
            deletePhonebook(&phonebook);
            return ok;
        }
        else if (command == 1)
        {
            printf("Введите 1, если хотите отсортировать по имени, 2 - если по номеру: ");
            int parameter = 0;
            if (scanf_s("%d", &parameter) != 1 || parameter != 1 && parameter != 2)
            {
                deletePhonebook(&phonebook);
                return INCORRECT_INPUT;
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
    return ok;
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