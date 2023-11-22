#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

void deleteEverySecondElement(List* list)
{
    ListErrorCode errorCode = ok;
    ListElement* current = getListElement(list, 0, &errorCode);
    if (errorCode != ok)
    {
        return;
    }
    while (current != NULL)
    {
        if (delete(&current, 1) != ok)
        {
            break;
        }
    }
}

bool listTest(void)
{
    bool testCases[3] = { true, true, true };
    List* list = createList();
    ListErrorCode errorCode = ok;
    int checkArray[3] = { 1, 2, 3 };
    add(list, 1);
    add(list, 2);
    add(list, 3);
    for (int i = 0; i < 3; ++i)
    {
        ListElement* current = getListElement(list, i, &errorCode);
        if (errorCode != ok)
        {
            testCases[0] = false;
            break;
        }
        
        if (getValue(current, &errorCode) != checkArray[i] || errorCode != ok)
        {
            testCases[0] = false;
            break;
        }
    }
    deleteList(&list);
    list = createList();
    errorCode = ok;
    checkArray[2] = 5;
    add(list, 1);
    add(list, 2);
    add(list, 2);
    add(list, 5); 
    ListElement* elementToDisorder = getListElement(list, 0, &errorCode);
    delete(&elementToDisorder, 2);
    for (int i = 0; i < 3; ++i)
    {
        ListElement* current = getListElement(list, i, &errorCode);
        if (errorCode != ok)
        {
            testCases[1] = false;
            break;
        }
        if (getValue(current, &errorCode) != checkArray[i] || errorCode != ok)
        {
            testCases[1] = false;
            break;
        }
    }
    deleteList(&list);
    list = createList();
    errorCode = ok;
    checkArray[0] = 2;
    add(list, 2);
    add(list, 1);
    add(list, 2);
    add(list, 5);
    elementToDisorder = getListElement(list, 0, &errorCode);
    elementToDisorder = getListElement(list, 0, &errorCode);
    delete(&elementToDisorder, 1);
    for (int i = 0; i < 3; ++i)
    {
        ListElement* current = getListElement(list, i, &errorCode);
        if (errorCode != ok)
        {
            testCases[2] = false;
            break;
        }
        if (getValue(current, &errorCode) != checkArray[i] || errorCode != ok)
        {
            testCases[2] = false;
            break;
        }
    }
    bool compliteTests = true;
    for (int i = 0; i < 3; ++i)
    {
        if (!testCases[i])
        {
            printf("Programm is not working with test case %d\n", i + 1);
            compliteTests = false;
        }
    }
    return compliteTests;
}

bool testFunction(void)
{
    List* list = createList();
    ListErrorCode errorCode = ok;
    int checkArray[3] = { 2, 4, 6 };
    for (int i = 2; i < 7; ++i)
    {
        add(list, i);
    }
    deleteEverySecondElement(list);
    for (int i = 0; i < 3; ++i)
    {
        ListElement* current = getListElement(list, i, &errorCode);
        if (errorCode != ok)
        {
            printf("Function did not work");
            return false;
        }
        if (getValue(current, &errorCode) != checkArray[i] || errorCode != ok)
        {
            printf("Function did not work");
            return false;
        }
    }
}

int main()
{
    if (!listTest() || !testFunction())
    {
        return -1;
    }
    List* list = createList();
    for (int i = 1; i < 6; ++i)
    {
        add(list, i);
    }
    printList(list);
    deleteEverySecondElement(list);
    printList(list);
    deleteList(&list);
}
