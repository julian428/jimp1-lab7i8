#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define BUFSIZE 8192

int main(int argc, char **argv)
{
    char *filename = argc > 1 ? argv[1] : NULL;
    FILE *input = openFile(filename);
    if (input == NULL)
    {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        return 1;
    }

    int wordsToFindCount = argc - 2;

    // todo: oddzielic to do innego modulu
    wordsStorage_t *ws = malloc(wordsToFindCount * sizeof(wordsStorage_t));
    for (int i = 0; i < wordsToFindCount; i++)
    {
        ws[i] = malloc(sizeof(wordItem_t));
        ws[i]->word = argv[i + 2];
        ws[i]->linesCount = 0;
    }

    char buf[BUFSIZE];
    for (int line = 1; fgets(buf, BUFSIZE, input) != NULL; line++)
    {
        for (int i = 0; i < wordsToFindCount; i++)
        {
            if (checkWords(buf, ws[i]->word))
            {
                ws[i]->lines[ws[i]->linesCount] = line;
                ws[i]->linesCount += 1;
            }
        }
    }

    printLines(ws, wordsToFindCount, stdout);

    // todo: oddzielic to do innego modulu
    for (int i = 0; i < wordsToFindCount; i++)
    {
        free(ws[i]);
    }
    free(ws);
    fclose(input);

    return 0;
}