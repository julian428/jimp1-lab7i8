#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv)
{
    FILE *input = openFile(argc > 1 ? argv[1] : NULL);

    if (input == NULL)
    {
        fprintf(stderr, "Error: cannot open file\n");
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

    checkWords(input, ws, wordsToFindCount);

    printLines(ws, wordsToFindCount, stdout);
    freeWordsMemory(ws, wordsToFindCount);
    fclose(input);

    return 0;
}