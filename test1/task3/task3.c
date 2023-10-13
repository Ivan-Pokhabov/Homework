#include <stdio.h>﻿
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    errno_t err;
    FILE *file;
    err = fopen_s(&file, "test.txt", "r");
    if (file == NULL)
    {
        printf("file not found!");
        return 1;
    }
    while (!feof(file))
    {
        char* buffer = malloc(sizeof(char) * 10000);
        const int readBytes = fscanf_s(file, "%s", buffer, 10000);
        if (readBytes < 0)
        {
            break;
        }
        bool comment = false;
        for (int i = 0; i < strlen(buffer); ++i)
        {
            if (buffer[i] == ';')
            {
                comment = true;
            }
            if (comment)
            {
                printf("%c", buffer[i]);
            }
        }
        if (comment)
        {
            printf("\n");
        }
    }
    fclose(file);
}

