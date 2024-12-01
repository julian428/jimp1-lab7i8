#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct wordItem
{
    char *word;
    int lines[100];
    int linesCount;
} wordItem_t, *wordsStorage_t;

FILE *openFile(char *filename);
wordsStorage_t *newWordsStorage(int wordsCount, char **words);
void checkWords(FILE *file, wordsStorage_t *storage, int wordsCount);
void printLines(wordsStorage_t *storage, int wordsStorageSize, FILE *output, int sort);
int compareStorage(const void *a, const void *b);
void freeWordsMemory(wordsStorage_t *ws, int wordsCount);
#endif