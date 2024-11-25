#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>

typedef struct wordItem
{
    char *word;
    int lines[100];
    int linesCount;
} wordItem_t, *wordsStorage_t;

FILE *openFile(char *filename);
int checkWords(char *source, char *word);
void printLines(wordsStorage_t *storage, int wordsStorageSize, FILE *output);
#endif