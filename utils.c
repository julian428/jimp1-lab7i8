#include "utils.h"

#define BUFSIZE 1024

int_vec* intvec_new(size_t initialCapacity)
{
    int_vec *vec = (int_vec *)malloc(sizeof(int_vec));
    if (!vec)
    {
        perror("int_vec malloc failed");
        exit(EXIT_FAILURE);
    }
    intvec_init(vec, initialCapacity);
    return vec;
}

void intvec_init(int_vec *vec, size_t initialCapacity)
{
    vec->data = (int *)malloc(initialCapacity * sizeof(int));
    if (!vec->data)
    {
        perror("int_vec malloc failed");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = initialCapacity;
}

void intvec_pushback(int_vec *vec, int value)
{
    if (vec->size == vec->capacity)
    {
        // Resize the vector when full
        vec->capacity *= 2;
        int *newData = (int *)realloc(vec->data, vec->capacity * sizeof(int));
        if (!newData)
        {
            perror("int_vec realloc failed memory");
            exit(EXIT_FAILURE);
        }
        vec->data = newData;
    }
    vec->data[vec->size++] = value;
}

int intvec_getitem(int_vec *vec, size_t index)
{
    if (index >= vec->size)
    {
        fprintf(stderr, "int_vec: index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    return vec->data[index];
}

void freeVector(int_vec *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

FILE *openFile(char *filename)
{
    return filename != NULL ? fopen(filename, "r") : stdin;
}

wordsStorage_t *newWordsStorage(int wordsCount, char **words)
{
    wordsStorage_t *ws = malloc(wordsCount * sizeof(wordItem_t *));
    for (int i = 0; i < wordsCount; i++)
    {
        ws[i] = malloc(sizeof(wordItem_t));
        ws[i]->word = words[i];
        ws[i]->lines = intvec_new(100);
    }
    return ws;
}

// TODO: co robić jak jedno słowo występuje kilka razy w jednej linii?
// Nic, jak dla mnie tak powinno być
void checkWords(FILE *file, wordsStorage_t *storage, int wordsCount)
{
    // linia moze wykraczac poza BUFSIZE,
    // bo robimy line++ tylko jak jest \n na koncu
    // tak powinno być optymalniej niż robienie malloc(fileSize)
    // bo co jak plik ma 100 GB?
    char buf[BUFSIZE];
    int line = 1;
    while (fgets(buf, BUFSIZE, file) != NULL)
    {
        /**
         * uzywamy strlen() bo nie wiemy jaki rzeczywisty rozmiar
         * linijki został wczytany
         */
        int readLen = strlen(buf);
        char lastChar = buf[readLen - 1];

        /**
         * tokenizujemy linijke po spacji i tabach
         * i sprawdzamy czy slowo jest w naszej tablicy
         * jesli tak to dodajemy numer linijki
         * dla tablicy tego slowa
         */
        char *lastTokenPtr;
        char *token = strtok_r(buf, " \t", &lastTokenPtr);
        while (token != NULL)
        {
            for (int i = 0; i < wordsCount; i++)
            {
                if (strcmp(token, storage[i]->word) == 0)
                {
                    intvec_pushback(storage[i]->lines, line);
                }
            }
            token = strtok_r(NULL, " \t", &lastTokenPtr);
        }

        /**
         * strtok() zmienia bufor, wiec musimy sprawdzic
         * czy nie ma \n na koncu przed podzieleniem na tokeny
         */
        if (lastChar == '\n')
            line++;
    }
}

int compareStorage(const void *a, const void *b)
{
    const wordItem_t *item1 = *(const wordItem_t **)a;
    const wordItem_t *item2 = *(const wordItem_t **)b;
    return strcmp(item1->word, item2->word);
}

int compareByLinesCount(const void *a, const void *b)
{
    const wordItem_t *item1 = *(const wordItem_t **)a;
    const wordItem_t *item2 = *(const wordItem_t **)b;
    // return item2->linesCount < item1->linesCount; // Descending order
    return item1->lines->size - item2->lines->size;
}

void printLines(wordsStorage_t *storage, int wordsStorageCount, FILE *output, int sort)
{
    if (sort == 1)
    {
        qsort(storage, wordsStorageCount, sizeof(wordsStorage_t), compareStorage);
    }
    else if (sort == 2)
    {
        qsort(storage, wordsStorageCount, sizeof(wordsStorage_t), compareByLinesCount);
    }

    for (int i = 0; i < wordsStorageCount; i++)
    {
        fprintf(output, "%s: ", storage[i]->word);
        for (int j = 0; j < storage[i]->lines->size; j++)
        {
            fprintf(output, "%d ", intvec_getitem(storage[i]->lines, j));
        }
        fprintf(output, "\n");
    }
}

void freeWordsMemory(wordsStorage_t *ws, int wordsCount)
{
    for (int i = 0; i < wordsCount; i++)
    {
        free(ws[i]);
    }
    free(ws);
}
