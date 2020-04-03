#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "./../include/FileManager.h"

int WriteFromFile(const char *fileName, char *string)
{
    FILE *filePtr = fopen(fileName, "w+");
    if (filePtr == NULL)
    {
        printf("Could not open file.\n");
        fclose(filePtr);
        return -1;
    }

    int res = fprintf(filePtr, "%s", string);
    if (res < 0)
    {
        printf("Could not write %s to file.\n", string);
        fclose(filePtr);
        return res;
    }

    fclose(filePtr);
    return 0;
}

int ReadFromFile(const char *fileName, char *string, int strSize)
{
    FILE *filePtr = fopen(fileName, "r+");
    if (filePtr == NULL)
    {
        printf("Could not open file.\n");
        fclose(filePtr);
        return -1;
    }

    if (fgets(string, strSize, filePtr) == NULL)
    {
        printf("Could not read from file.\n");
        fclose(filePtr);
        return -2;
    }

    fclose(filePtr);
    return 0;
}