#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int *data;       // Pointer to the array storing integers
    size_t size;     // Current number of elements
    size_t capacity; // Maximum capacity before resizing
} int_vec;

int_vec *intvec_new(size_t initialCapacity);
void intvec_init(int_vec *vec, size_t initialCapacity);
void intvec_pushback(int_vec *vec, int value);
int intvec_getitem(int_vec *vec, size_t index);
void intvec_free(int_vec *vec);

typedef struct wordItem
{
    char *word;
    int_vec *lines;
} wordItem_t, *wordsStorage_t;

FILE *openFile(char *filename);
wordsStorage_t *newWordsStorage(int wordsCount, char **words);
void checkWords(FILE *file, wordsStorage_t *storage, int wordsCount);
void printLines(wordsStorage_t *storage, int wordsStorageSize, FILE *output, int sort);
int compareStorage(const void *a, const void *b);
void freeWordsMemory(wordsStorage_t *ws, int wordsCount);
#endif