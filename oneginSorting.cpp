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

int main()
{
    char *buffer = NULL;

    if (readFromFile("onegin.txt", O_RDONLY, &buffer) == -1)
    {
        return -1;
    }

    int nLines = 0;
    char *temp = buffer;
    while ((temp = strchrMy(temp, '\n')) != NULL)
    {
        nLines++;
        temp++;
    }

    if (buffer[0] != '\0' && *(temp - 1) != '\n')
    {
        nLines++;
    }

    arrayParameter *index = (struct arrayParameter *)calloc(nLines,
                                                            sizeof(struct arrayParameter));
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

    qSort(index, nLines, strComparatorDown, sizeof(arrayParameter));

    writeToFile(index, nLines, filePointerWrite);

    qsort(index, nLines, sizeof(arrayParameter), strComparatorFromEnd);

    writeToFile(index, nLines, filePointerWrite);

    qSort(index, nLines, ptrComparator, sizeof(arrayParameter));

    writeToFile(index, nLines, filePointerWrite);

    fclose(filePointerWrite);

    safeFree(&buffer);

    return 0;
}
