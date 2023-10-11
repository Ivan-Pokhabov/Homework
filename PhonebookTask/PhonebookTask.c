#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    char name[100];
    char number[100];
} Phonebook;

void add(Phonebook phonebook[], const int currentPosition)
{
    if (currentPosition == 100)
    {
        printf("Телефонная книга переполнена.");
        return;
    }
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

void getFileData(const char fileName[], Phonebook phonebook[], int *currentPosition)
{
    FILE* file;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return;
    }
    int cologn = 0;
    while (!feof(file))
    {
        char buffer[100];
        const int readbytes = fscanf_s(file, "%s", buffer, _countof(buffer));
        if (readbytes < 0)
        {
            break;
        }
        if (cologn == 0)
        {
            strcpy_s(phonebook[*currentPosition].name, _countof(phonebook[*currentPosition].name), buffer);
        }
        else
        {
            strcpy_s(phonebook[*currentPosition].number, _countof(phonebook[*currentPosition].number), buffer);
            ++*currentPosition;
        }
        cologn ^= 1;
    }
    fclose(file);
}

void saveFile(const char fileName[], Phonebook phonebook[], const int currentPosition)
{
    FILE* file;
    fopen_s(&file, fileName, "w");
    if (file == NULL)
    {
        return;
    }
    for (int i = 0; i < currentPosition; ++i)
    {
        fprintf(file, "%s %s\n", phonebook[i].name, phonebook[i].number);
    }
    fclose(file);
}

void instructions(void)
{
    printf("0 - выйти\n");
    printf("1 - добавить запись(имя и телефон)\n");
    printf("2 - распечатать все имеющиеся записи\n");
    printf("3 - найти телефон по имени\n");
    printf("4 - найти имя по телефону\n");
    printf("5 - сохранить текущие данные в файл\n");
}

void solve(void)
{
    Phonebook phonebook[100];
    int notesCount = 0;
    getFileData("database.txt", phonebook, &notesCount);
    instructions();
    const int command = -1;
    while (command != 0)
    {
        if (scanf_s("%d", &command) != 1 || command > 5 || command < 0)
        {
            printf("Вы ввели некорректное значение.");
            continue;
        }
        if (command == 0)
        {
            return;
        }
        else if (command == 1)
        {
            add(phonebook, notesCount);
            ++notesCount;
        }
        else if (command == 2)
        {
            print(phonebook, notesCount);
        }
        else if (command == 3)
        {
            printf("Введите имя: ");
            const char name[100];
            scanf_s("%s", name, _countof(name));
            findNumber(name, phonebook, notesCount);
        }
        else if (command == 4)
        {
            printf("Введите номер: ");
            const char number[100];
            scanf_s("%s", number, _countof(number));
            findName(number, phonebook, notesCount);
        }
        else
        {
            saveFile("database.txt", phonebook, notesCount);
        }
    }
}

bool getFileDataTest(Phonebook testbook[], const int notesCount)
{
    if (notesCount == 3)
    {
        return strcmp(testbook[0].name, "Vanya") == 0 && strcmp(testbook[0].number, "111-111") == 0 && strcmp(testbook[1].name, "HochuPitsu") == 0 &&
            strcmp(testbook[1].number, "1337228") == 0 && strcmp(testbook[2].name, "Nastya:)") == 0 && strcmp(testbook[2].number, "+7913575??45") == 0;
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    solve();
}