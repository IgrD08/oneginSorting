void swap(void *firstValue, void *secondValue, size_t sizeType);
void qSort(void *array, size_t arrayLen,
           int (*comparator)(const void* first, const void* second), size_t sizeType);
int strComparatorDown(const void *first, const void *second);
int strComparatorFromEnd(const void *first, const void *second);
int ptrComparator(const void *first, const void *second);

void qSort(void *array, size_t arrayLen,
           int (*comparator)(const void* first, const void* second), size_t sizeType)
{
    assert(array);

    if (arrayLen <= 1) return;

    uint8_t *last = (uint8_t*)array + (arrayLen - 1) * sizeType;
    size_t quantityLessLast = 0;

    for (size_t i = 0; i < arrayLen - 1; i++)
    {
        if (comparator((uint8_t*)array + i * sizeType, last) > 0)
        {
            swap((uint8_t*)array + quantityLessLast * sizeType,
                 (uint8_t*)array + i * sizeType, sizeType);
            quantityLessLast++;
        }
    }
    swap((uint8_t*)array + quantityLessLast * sizeType,
         (uint8_t*)array + (arrayLen - 1) * sizeType, sizeType);

    qSort((uint8_t*)array, quantityLessLast, comparator, sizeType);

    qSort((uint8_t*)array + (quantityLessLast + 1) * sizeType,
          arrayLen - quantityLessLast - 1, comparator, sizeType);
    return;
}

void swap(void *firstValue, void *secondValue, size_t sizeType)
{
    assert(firstValue);
    assert(secondValue);

    char temp = 0;

    for (size_t i = 0; i < sizeType; i++)
    {
        memcpy(&temp, ((char*)firstValue) + i, 1);
        memcpy(((char*)firstValue) + i, ((char*)secondValue) + i, 1);
        memcpy(((char*)secondValue + i), &temp, 1);
    }

    return;
}

int strComparatorDown(const void *first, const void *second)
{
    assert(first);
    assert(second);

    const char *firstString = *((const char*const*) first);
    const char *secondString = *((const char*const*) second);
    int firstCounter = 0, secondCounter = 0;

    while ((firstString[firstCounter])  != '\0' &&
           (secondString[secondCounter]) != '\0')
    {
        while (!isalpha(firstString[firstCounter]) &&
               firstString[firstCounter] != '\0') firstCounter++;
        while (!isalpha(secondString[secondCounter]) &&
               secondString[secondCounter] != '\0') secondCounter++;

        if (firstString[firstCounter] == '\0' || secondString[secondCounter] == '\0')
        {
            break;
        }

        if (tolower(firstString[firstCounter]) != tolower(secondString[secondCounter]))
        {
            return tolower(secondString[secondCounter]) - tolower(firstString[firstCounter]);
        }

        firstCounter++;
        secondCounter++;
    }

    return secondString[secondCounter] - firstString[firstCounter];
}

int strComparatorFromEnd(const void *first, const void *second)
{
    assert(first);
    assert(second);

    const char *firstString = *((const char*const*)first);
    const char *secondString = *((const char*const*)second);
    int firstCounter = 0, secondCounter = 0;

    while ((firstString[firstCounter]) != '\0') firstCounter++;

    while ((secondString[secondCounter]) != '\0') secondCounter++;

    int i = firstCounter - 1;
    int j = secondCounter - 1;
    for (; i >= 0 && j >= 0; i--, j--)
    {
        while (!isalpha(firstString[i]) && i >= 1) i--;
        while (!isalpha(secondString[j]) && j >= 1) j--;

        int charFirst = tolower(firstString[i]);
        int charSecond = tolower(secondString[j]);

        if (charFirst != charSecond)
        {
            return charFirst - charSecond;
        }
    }

    return i - j;
}

int ptrComparator(const void *first, const void *second)
{
    assert(first);
    assert(second);

    const uintptr_t firstValue = *((const uintptr_t *)first);
    const uintptr_t secondValue = *((const uintptr_t *)second);

    return secondValue - firstValue;
}
