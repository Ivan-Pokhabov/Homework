#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "FileTask.h"

Error solveFileTask(const char* const arrayFileName, const char* const numberFileName, const char* const outputFileName)
{
    FILE* arrayFile = NULL;
    fopen_s(&arrayFile, arrayFileName, "r");
    if (arrayFile == NULL)
    {
        return fileDidNotOpen;
    }
    FILE* numberFile = NULL;
    fopen_s(&numberFile, numberFileName, "r");
    if (numberFile == NULL)
    {
        fclose(arrayFile);
        return fileDidNotOpen;
    }
    int number = 0;
    if (fscanf_s(numberFile, "%d", &number) != 1)
    {
        fclose(numberFile);
        fclose(arrayFile);
        return incorrectInputFile;
    }
    int arrayNumber = 0;
    FILE* writeFile = NULL;
    fopen_s(&writeFile, outputFileName, "w");
    if (writeFile == NULL)
    {
        fclose(numberFile);
        fclose(arrayFile);
        return fileDidNotOpen;
    }
    while (fscanf_s(arrayFile, "%d", &arrayNumber) == 1)
    {
        if (arrayNumber < number)
        {
            fprintf(writeFile, "%d ", arrayNumber);
        }
    }
    fclose(arrayFile);
    fclose(numberFile);
    fclose(writeFile);
    return ok;
}