#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include "sorting.cpp"

const int MAX_STR = 10000;

int readFromFile(char **text, char **index, const char *fileName);
void writeToFile(char **index, int numberOfReadLines, FILE *filePointerLines);

int main()
{
//TODO - сделать структуры, заменить на fread
    char *text[MAX_STR] = {};
    char *index[MAX_STR] = {};

    int nLines = readFromFile(text, index, "onegin.txt");

    FILE *filePointerWrite = fopen("reonegin.txt", "w");

    if (filePointerWrite == NULL)
    {
        fprintf(stderr, "Unable to open %s\n", "reonegin.txt");
        return 0;
    }

    qSort(index, nLines, strComparatorDown, sizeof(char*));

    writeToFile(index, nLines, filePointerWrite);

    qsort(index, nLines, sizeof(char*), strComparatorFromEnd);

    writeToFile(index, nLines, filePointerWrite);

    writeToFile(text, nLines, filePointerWrite);

    fclose(filePointerWrite);

    return 0;
}

int readFromFile(char **text, char **index, const char *fileName)
{
    assert(fileName);
    assert(index);
    assert(text);

    FILE *filePointerRead = fopen(fileName, "r");
    int numberOfReadLines = 0;

    if (filePointerRead == NULL)
    {
        fprintf(stderr, "Unable to open %s\n", fileName);
        return -2;
    }

    char buffer[MAX_STR] = "";

    while (numberOfReadLines < MAX_STR && fgets(buffer, sizeof(buffer), filePointerRead) != NULL)
    {
        size_t lenBuffer = strlen(buffer);

        if (lenBuffer > 0 && buffer[lenBuffer - 1] == '\n')
        {
            buffer[lenBuffer - 1] = '\0';
        }

        text[numberOfReadLines] = strdup(buffer);
        //TODO - free() использовать обёртку и применить
        index[numberOfReadLines] = text[numberOfReadLines];

        numberOfReadLines++;
    }

    fclose(filePointerRead);

    return numberOfReadLines;
}

void writeToFile(char **index, int numberOfReadLines, FILE *filePointerWrite)
{
    assert(index);
    assert(filePointerWrite);

    for (int i = 0; i < numberOfReadLines; i++)
    {
        fprintf(filePointerWrite, "<<%s>>\n", index[i]);
    }

    fprintf(filePointerWrite, "*****************************************\n");

    return;
}
