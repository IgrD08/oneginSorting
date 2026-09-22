struct arrayParameter
{
    char *array;
    size_t arrayLen;
};

const int MAX_STR = 10000;

int readFromFile(arrayParameter *index, const char *fileName, int flag, char **bufferPtr);
int writingToStruct(arrayParameter *index, char **bufferPtr);
void writeToFile(arrayParameter *index, int numberOfReadLines, FILE *filePointerWrite);
int fileOpening(const char *fileName, int flag);
char* strchrMy(char *str, int ch);
void safeFree(char **bufferPtr);

int readFromFile(arrayParameter *index, const char *fileName, int flag, char **bufferPtr)
{
    assert(fileName);
    assert(index);
    assert(bufferPtr);

    int fileDescriptorRead = fileOpening(fileName, flag);
    if (fileDescriptorRead < 0) return -1;

    struct stat fileInfo;
    if (stat(fileName, &fileInfo) == -1) return -1;

    *bufferPtr = (char*) (calloc(fileInfo.st_size + 1, sizeof(char)));

    ssize_t numberOfBytesRead = read(fileDescriptorRead, *bufferPtr, fileInfo.st_size + 1);
    if (numberOfBytesRead == -1) return -1;

    if (close(fileDescriptorRead) == -1) printf("Unable to close\n");

    (*bufferPtr)[numberOfBytesRead] = '\0';
    (*bufferPtr)[fileInfo.st_size] = '\0';

    return 0;
}

int writingToStruct(arrayParameter *index, char **bufferPtr)
{
    assert(bufferPtr);

    int numberOfReadLines = 0;
    char *element = *bufferPtr;
    char *firstElement = *bufferPtr;

    if (*firstElement != '\0' && numberOfReadLines < MAX_STR)
    {
        index[numberOfReadLines].array = firstElement;
    }

    while ((element = strchrMy(element, '\n')) != NULL)
    {
        *element = '\0';

        index[numberOfReadLines].arrayLen = element - firstElement;
        numberOfReadLines++;

        char *nextLine = element + 1;

        index[numberOfReadLines].array = nextLine;
        firstElement = nextLine;
        element = nextLine;
    }

    return numberOfReadLines;
}

void writeToFile(arrayParameter *index, int numberOfReadLines, FILE *filePointerWrite)
{
    assert(index);
    assert(filePointerWrite);

    for (int i = 0; i < numberOfReadLines; i++)
    {
        if (index[i].array != NULL)
        {
            fprintf(filePointerWrite, "<<%s>>\n", index[i].array);
        }
    }

    fprintf(filePointerWrite, "*****************************************\n");

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
    assert(str);

    while (*str != '\0')
    {

        if (*str == ch)
            return str;

        str++;
    }
    return NULL;
}

void safeFree(char **bufferPtr)
{
    assert(bufferPtr);

    if (bufferPtr != NULL && *bufferPtr != NULL) {
        **bufferPtr = '0';
        free(*bufferPtr);
        *bufferPtr = NULL;

    }
}
