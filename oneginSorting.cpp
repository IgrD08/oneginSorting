#include "file.h"

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
