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
    struct arrayParameter index[MAX_STR] = {NULL};
    char *buffer = NULL;

    int nLines = readFromFile(index, "onegin.txt", O_RDONLY, &buffer);

    FILE * filePointerWrite = fopen("reonegin.txt", "w");
    if (filePointerWrite == NULL)
    {
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
