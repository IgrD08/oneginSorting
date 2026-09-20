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

const int MAX_STR = 10000;

int readFromFile(char **index, const char *fileName, int flag, char **bufferPtr);
void writeToFile(char **index, int numberOfReadLines, int fileDescriptor);
int fileOpening(const char *fileName, int flag);
char* strchrMy(char *str, int ch);

int main()
{
    char *index[MAX_STR] = {NULL};
    char *buffer = NULL;

    int nLines = readFromFile(index, "onegin.txt", O_RDONLY, &buffer);

    int fileDescriptorWrite = fileOpening("reonegin.txt", O_WRONLY);

    qSort(index, nLines, strComparatorDown, sizeof(char*));

    writeToFile(index, nLines, fileDescriptorWrite);

    qsort(index, nLines, sizeof(char*), strComparatorFromEnd);//TODO - массив структур

    writeToFile(index, nLines, fileDescriptorWrite);

//     qSort(index, nLines, intComparator, sizeof(int));
//
//     writeToFile(index, nLines, fileDescriptorWrite);

    close(fileDescriptorWrite);

    free(buffer); //TODO - прокачать free


    return 0;
}

int readFromFile(char **index, const char *fileName, int flag, char **bufferPtr)
{
    assert(fileName);
    assert(index);
    assert(bufferPtr);

    int fileDescriptorRead = fileOpening(fileName, flag);//TODO можно ли возвращать код ошибки
    if (fileDescriptorRead < 0) return -1;

    struct stat fileInfo;
    stat(fileName, &fileInfo);//TODO что возвращает stat

    *bufferPtr = (char*) (calloc(fileInfo.st_size + 1, sizeof(char)));

    read(fileDescriptorRead, *bufferPtr, fileInfo.st_size + 1);
    (*bufferPtr)[fileInfo.st_size] = '\0';
    close(fileDescriptorRead);

    int numberOfReadLines = 0;

    index[numberOfReadLines] = *bufferPtr;
    numberOfReadLines++;

    char *element = *bufferPtr;

    while ((element = strchr(element, '\n')) != NULL)//TODO - проход по строке
    {
        *element = '\0';

        char *nextLine = element + 1;

        if (*nextLine != '\0' && numberOfReadLines < MAX_STR)
        {
            index[numberOfReadLines] = nextLine;
            numberOfReadLines++;
        }

        element = nextLine;
    }

    return numberOfReadLines;
}

void writeToFile(char **index, int numberOfReadLines, int fileDescriptor)
{
    assert(index);

    for (int i = 0; i < numberOfReadLines; i++)
    {
        if (index[i] != NULL)
        {
            write(fileDescriptor, index[i], strlen(index[i]));
            write(fileDescriptor, "\n", 1);
        }
    }

    const char *text = "*****************************************\n";

    write(fileDescriptor, text, 42);

    return;
}

int fileOpening(const char *fileName, int flag)
{
    int fileDescriptor = open(fileName, flag);

    if (fileDescriptor == -1)
    {
        fprintf(stderr, "Unable to open %s\n", fileName);

        return fileDescriptor;
    }

    return fileDescriptor;
}

char* strchrMy(char *str, int ch)
{

    while (*str != '\0')
    {

        if (*str == ch)
            return str;

        str++;
    }
    return NULL;
}
