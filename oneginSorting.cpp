#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "fileProcessing.cpp"
#include "sorting.cpp"

void sortAndWrite(struct arrayParameter *index, int nLines, FILE *fp);
int countLines(char *buffer);

int main()
{
    char *buffer = NULL;
    if (readFromFile("onegin.txt", O_RDONLY, &buffer) == -1) return -1;

    int nLines = countLines(buffer);

    struct arrayParameter *index = (struct arrayParameter *)
                                    calloc(nLines, sizeof(struct arrayParameter));
    if (index == NULL)
    {
        safeFree(&buffer);
        return -1;
    }

    writingToStruct(index, &buffer);

    FILE *filePointerWrite = fopen("reonegin.txt", "w");
    if (filePointerWrite == NULL)
    {
        free(index);
        safeFree(&buffer);
        return -1;
    }

    sortAndWrite(index, nLines, filePointerWrite);

    fclose(filePointerWrite);
    free(index);
    safeFree(&buffer);

    return 0;
}

int countLines(char *buffer)
{
    int nLines = 0;
    char *temp = buffer;
    while ((temp = strchrMy(temp, '\n')) != NULL)
    {
        nLines++;
        temp++;
    }
    if (buffer[0] != '\0' && *(temp - 1) != '\n') nLines++;

    return nLines;
}

void sortAndWrite(struct arrayParameter *index, int nLines, FILE *fp)
{
    qSort(index, nLines, strComparatorDown, sizeof(arrayParameter));
    writeToFile(index, nLines, fp);

    qsort(index, nLines, sizeof(arrayParameter), strComparatorFromEnd);
    writeToFile(index, nLines, fp);

    qSort(index, nLines, ptrComparator, sizeof(arrayParameter));
    writeToFile(index, nLines, fp);

    return;
}
