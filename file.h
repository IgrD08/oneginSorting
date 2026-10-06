#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

struct arrayParameter
{
    char *array;
    size_t arrayLen;
};

int readFromFile(const char *fileName, int flag, char **bufferPtr);
int writingToStruct(arrayParameter *index, char **bufferPtr);
void writeToFile(arrayParameter *index, int numberOfReadLines, FILE *filePointerWrite);
void sortAndWrite(struct arrayParameter *index, int nLines, FILE *fp);
int countLines(char *buffer);
int fileOpening(const char *fileName, int flag);
char* strchrMy(char *str, int ch);
void safeFree(char **bufferPtr);


void swap(void *firstValue, void *secondValue, size_t sizeType);
void qSort(void *array, size_t arrayLen,
           int (*comparator)(const void* first, const void* second), size_t sizeType);
int strComparatorDown(const void *first, const void *second);
int strComparatorFromEnd(const void *first, const void *second);
int ptrComparator(const void *first, const void *second);

#endif
