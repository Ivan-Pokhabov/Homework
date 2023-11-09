#include "Test.h"
#include "Phonebook.h"

#include <stdbool.h>
#include <stdlib.h>

bool test(void)
{
    char* tests[3] = {"test1.txt", "test2.txt", "test3.txt"};
    bool passed = true;
    for (int i = 0; i < 3; ++i)
    {
        Phonebook* phonebook = createPhonebook();
        PhonebookErrorCode errorCode = ok;
        size_t size = 0;
        if (getFileData(tests[i], phonebook, &size) != ok)
        {
            printf("Îøèáêà ÷òåíèÿ èç ôàéëà\n");
            passed = false;
            continue;
        }
        mergeSort(phonebook, 0, size, 1, &errorCode);
        if (errorCode != ok || checkSort(phonebook, 1))
        {
            printf("Îøèáêà ñîðòèðîâêè ïî èìåíè\n");
            passed = false;
        }
        errorCode = ok;
        mergeSort(phonebook, 0, size, 2, &errorCode);
        if (errorCode != ok || checkSort(phonebook, 2))
        {
            printf("Îøèáêà ñîðòèðîâêè ïî íîìåðó\n");
            passed = false;
        }
        deletePhonebook(&phonebook);
    }
    return passed;
}
