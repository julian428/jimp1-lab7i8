#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define BUFSIZE 8192

int main(int argc, char **argv)
{
    char *filename = argc > 2 ? argv[1] : NULL;
    FILE *input = openFile(filename);
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
            if (checkWords(buf, ws[i]->word))
            {
                ws[i]->lines[ws[i]->linesCount] = line;
                ws[i]->linesCount += 1;
            }
        }
    }

    printLines(ws, wordsToFindCount, stdout);
}