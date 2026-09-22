struct arrayParameter
{
    char *array;
    size_t arrayLen;
};

const int MAX_STR = 10000;

int readFromFile(char **index, const char *fileName, int flag, char **bufferPtr);
void writeToFile(char **index, int numberOfReadLines, int fileDescriptor);
int fileOpening(const char *fileName, int flag);
char* strchrMy(char *str, int ch);
void safeFree(char **bufferPtr);

int readFromFile(char **index, const char *fileName, int flag, char **bufferPtr)
{
    assert(fileName);
    assert(index);
    assert(bufferPtr);

    int fileDescriptorRead = fileOpening(fileName, flag);//TODO можно ли возвращать код ошибки
    if (fileDescriptorRead < 0) return -1;

    struct stat fileInfo;
    if (stat(fileName, &fileInfo) == -1) return -1;

    *bufferPtr = (char*) (calloc(fileInfo.st_size + 1, sizeof(char)));

    ssize_t numberOfBytesRead = read(fileDescriptorRead, *bufferPtr, fileInfo.st_size + 1);
    if (numberOfBytesRead == -1) return -1;

    (*bufferPtr)[numberOfBytesRead] = '\0';
    (*bufferPtr)[fileInfo.st_size] = '\0';

    if (close(fileDescriptorRead) == -1) return -1;

    int numberOfReadLines = 0;

    index[numberOfReadLines] = *bufferPtr;
    numberOfReadLines++;

    char *element = *bufferPtr;

    while ((element = strchrMy(element, '\n')) != NULL)
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

void safeFree(char **bufferPtr)
{
    assert(bufferPtr);

    if (bufferPtr != NULL && *bufferPtr != NULL) {
        free(*bufferPtr);
        **bufferPtr = '0';
        *bufferPtr = NULL;

    }
}
