#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>

typedef struct wordItem
{
    char *word;
    int lines[100];
    int linesCount;
} wordItem_t, *wordsStorage_t;

FILE *openFile(char *filename);
int checkWords(char *source, char **words);
void printLines(wordsStorage_t *storage, FILE *output);
#endif