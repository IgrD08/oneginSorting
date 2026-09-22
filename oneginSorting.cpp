#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "sorting.cpp"
#include "fileProcessing.cpp"

int main()
{
    struct arrayParameter
    {
        char *array;
        size_t arrayLen;
    };

    char *index[MAX_STR] = {NULL};
    char *buffer = NULL;

    int nLines = readFromFile(index, "onegin.txt", O_RDONLY, &buffer);

    int fileDescriptorWrite = fileOpening("reonegin.txt", O_WRONLY);

    qSort(index, nLines, strComparatorDown, sizeof(char*));

    writeToFile(index, nLines, fileDescriptorWrite);

    qsort(index, nLines, sizeof(char*), strComparatorFromEnd);//TODO - массив структур

    writeToFile(index, nLines, fileDescriptorWrite);

    qSort(index, nLines, ptrComparator, sizeof(int));

    writeToFile(index, nLines, fileDescriptorWrite);

    close(fileDescriptorWrite);

    free(&buffer);

    return 0;
}
