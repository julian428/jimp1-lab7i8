#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "utils.h"

#define BUFSIZE 8192

typedef struct wordItem
{
    char *word;
    int lines[100];
    int linesCount;
} wordItem_t, *wordsStorage_t;

int main(int argc, char **argv)
{
    char *filename = argc > 2 ? argv[1] : stdin;
    // FILE *input = openFile(filename);
    FILE *input = fopen(filename, "r");
    if (input == NULL)
    {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        return 1;
    }

    // TODO split module
    int wordsToFindCount = argc - 2;
    wordsStorage_t *ws = malloc(wordsToFindCount * sizeof(wordItem_t));
    for (int i = 0; i < wordsToFindCount; i++)
    {
        ws[i]->word = argv[i + 2];
    }

    // TODO split module
    char buf[BUFSIZE];
    for (int line = 1; fgets(buf, BUFSIZE, input) != NULL; line++)
    {
        for (int i = 0; i < wordsToFindCount; i++)
        {
            if (strstr(buf, ws[i]) != NULL)
            {
                ws[i]->lines[ws[i]->linesCount++] = line;
            }
        }
    }

    // TODO split module
    for (int i = 0; i < wordsToFindCount; i++)
    {
        printf("%s: ", ws[i]->word);
        for (int j = 0; j < ws[i]->linesCount; j++)
        {
            printf("%d ", ws[i]->lines[j]);
        }
        printf("\n");
    }
}