#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#include "AVLTree.h"

#define VALUE_SIZE 100

int main()
{
    setlocale(LC_ALL, "Russian");
    int command = 0;
    bool endOfProgram = false;
    AVLTree* tree = createAVLTree();
    while (!endOfProgram)
    {
        char key[VALUE_SIZE] = "";
        instructions();
        scanf_s("%d", &command);
        switch (command)
        {
        case 0:
            endOfProgram = true;
            break;
        case 1:
        {
            printf("Введите ключ: ");
            if (scanf_s("%s", key, VALUE_SIZE) != 1)
            {
                printf("Неверный ввод, повторите снова\n");
                break;
            }
            printf("Введите значение: ");
            char value[VALUE_SIZE];
            if (scanf_s("%s", value, VALUE_SIZE) != 1)
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
            if (scanf_s("%s", key, VALUE_SIZE) != 1)
            {
                printf("Неверный ввод, повторите снова\n");
                break;
            }
            char* value = getValue(tree, key);
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
            if (scanf_s("%s", key, VALUE_SIZE) != 1)
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
            if (scanf_s("%s", key, VALUE_SIZE) != 1)
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
    deleteAVLTree(&tree);
    return 0;
}
