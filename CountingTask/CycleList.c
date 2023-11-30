#include "CycleList.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct CycleListElement
{
    int value;
    struct CycleListElement* next;
};

struct CycleList
{
    CycleListElement* head;
};

CycleList* createCycleList(void)
{
    return calloc(1, sizeof(CycleList));
}

CycleListErrorCode add(CycleList* cycleList, const int index, const int value)
{
    if (cycleList == NULL)
    {
        return nullptr;
    }
    CycleListElement* newCycleListElement = calloc(1, sizeof(CycleListElement));
    if (newCycleListElement == NULL)
    {
        return memoryError;
    }
    newCycleListElement->value = value;
    CycleListErrorCode errorCode = ok;
    if (isEmpty(cycleList, &errorCode))
    {
        if (errorCode == nullptr)
        {
            return nullptr;
        }
        newCycleListElement->next = newCycleListElement;
        cycleList->head = newCycleListElement;
        return ok;
    }
    if (index == 1)
    {
        newCycleListElement->next = cycleList->head;
        cycleList->head = newCycleListElement;
        return ok;
    }
    CycleListElement* currentCycleListElement = cycleList->head;
    int currentIndex = 0;
    while (currentIndex < index - 2)
    {
        currentCycleListElement = currentCycleListElement->next;
        ++currentIndex;
    }
    newCycleListElement->next = currentCycleListElement->next;
    currentCycleListElement->next = newCycleListElement;
    return ok;
}

CycleListErrorCode delete(CycleList** cycleList, CycleListElement** element, const size_t index)
{
    CycleListErrorCode errorCode = ok;
    if (element == NULL || *element == NULL)
    {
        return nullptr;
    }
    if (index == 1)
    {
        CycleListElement* listElementToDisorder = (*element)->next;
        (*element)->value = listElementToDisorder->value;
        (*element)->next = (*element)->next->next;
        if (listElementToDisorder == (*cycleList)->head)
        {
            (*cycleList)->head = (*element)->next;
            if (listElementToDisorder == (*cycleList)->head)
            {
                (*cycleList)->head = NULL;
            }
        }
        free(listElementToDisorder);
        return ok;
    }
    int currentIndex = 0;
    while (currentIndex < index - 2)
    {
        *element = (*element)->next;
        ++currentIndex;
    }
    CycleListElement* listElementToDisorder = (*element)->next;
    (*element)->next = (*element)->next->next;
    if (listElementToDisorder == (*cycleList)->head)
    {
        (*cycleList)->head = (*element)->next;
        if (listElementToDisorder == (*cycleList)->head)
        {
            (*cycleList)->head = NULL;
        }
    }
    *element = (*element)->next;
    free(listElementToDisorder);
    return ok;
}

CycleListElement* next(CycleListElement* element, CycleListErrorCode* errorCode)
{
    if (element == NULL)
    {
        *errorCode == nullptr;
        return NULL;
    }
    return element->next;
}

CycleListElement* getListElement(CycleList* cycleList, const size_t position, CycleListErrorCode* errorCode)
{
    if (cycleList == NULL || isEmpty(cycleList, errorCode))
    {
        *errorCode = nullptr;
        return NULL;
    }
    CycleListElement* current = cycleList->head;
    for (size_t i = 1; i < position; ++i)
    {
        current = current->next;
        if (current == NULL)
        {
            *errorCode = getNonExistentElement;
            return NULL;
        }
    }
    return current;
}

bool isEmpty(CycleList* cycleList, CycleListErrorCode* errorCode)
{
    if (cycleList == NULL)
    {
        *errorCode = nullptr;
        return true;
    }
    return cycleList->head == NULL;
}

int get(CycleList* cycleList, const int index, CycleListErrorCode* errorCode)
{
    if (isEmpty(cycleList, errorCode))
    {
        *errorCode = nullptr;
        return -1;
    }
    int currentIndex = 0;
    CycleListElement* currentCycleListElement = cycleList->head;
    while (currentIndex < index - 1)
    {
        currentCycleListElement = currentCycleListElement->next;
        ++currentIndex;
    }
    return currentCycleListElement->value;
}

CycleListErrorCode printCycleList(CycleList* cycleList)
{
    if (cycleList == NULL)
    {
        return nullptr;
    }
    CycleListElement* current = cycleList->head;
    printf("%d ", current->value);
    current = current->next;
    while (current != cycleList->head)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
    return ok;
}

void deleteCycleList(CycleList** cycleList)
{
    if (cycleList == NULL || *cycleList == NULL)
    {
        return;
    }
    CycleListElement* current = (*cycleList)->head;
    while ((*cycleList)->head != current->next)
    {
        CycleListElement* trash = current;
        current = current->next;
        free(trash);
    }
    free(current);
    free(*cycleList);
    *cycleList = NULL;
}
