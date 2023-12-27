#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#include "Dictionary.h"
#include "Test.h"

void instructions(void)
{
    printf("0 - Выйти\n");
    printf("1 - Добавить значение по ключу\n");
    printf("2 - Получить значение по ключу\n");
    printf("3 - Проверить существование ключа\n");
    printf("4 - Удалить значение по ключу\n");
}

int main()
{
    if (!test())
    {
        return -1;
    }
    setlocale(LC_ALL, "Russian");
    int command = 0;
    bool endOfProgram = false;
    BinaryTree* tree = createBinaryTree();
    while (!endOfProgram)
    {
        instructions();
        scanf_s("%d", &command);
        int key = 0;
        switch (command)
        {
        case 0:
            endOfProgram = true;
            break;
        case 1:
        {
            printf("Введите ключ: ");
            if (scanf_s("%d", &key) != 1)
            {
                printf("Неверный ввод, повторите снова\n");
                break;
            }
            printf("Введите значение: ");
            char value[100] = "";
            if (scanf_s("%s", value, 100) != 1)
            {
                printf("Неверный ввод, повторите снова\n");
                break;
            }
            addValue(tree, key, value);
            break;
        }
        case 2:
        {
            printf("Введите ключ: ");
            if(scanf_s("%d", &key) != 1)
            {
                printf("Неверный ввод, повторите снова\n");
                break;
            }
            const char* value = getValue(tree, key);
            if (value != NULL)
            {
                printf("Значение: %s", value);
            }
            else
            {
                printf("Значение не найдено");
            }
            printf("\n");
            break;
        }
        case 3:
            printf("Введите ключ: ");
            if (scanf_s("%d", &key) != 1)
            {
                printf("Неверный ввод, повторите снова\n");
                break;
            }
            if (contains(tree, key))
            {
                printf("Ключ существует");
            }
            else
            {
                printf("Ключ не существует");
            }
            printf("\n");
            break;
        case 4:
            printf("Введите ключ: ");
            if (scanf_s("%d", &key) != 1)
            {
                printf("Неверный ввод, повторите снова\n");
                break;
            }
            deleteValue(tree, key);
            break;
        default:
            printf("Неверный ввод, повторите снова\n");
            break;
        }
        printf("\n");
    }
    deleteBinaryTree(&tree);
    return 0;
}

