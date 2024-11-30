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

FILE *openFile(char *filename, long *fileSize);
void checkWords(FILE *file, long fileSize, wordsStorage_t *storage, int wordsCount);
void printLines(wordsStorage_t *storage, int wordsStorageSize, FILE *output);
void freeWordsMemory(wordsStorage_t *ws, int wordsCount);
#endif