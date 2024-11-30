#include <stdio.h>
#include <string.h>
#include "utils.h"

#define BUFSIZE 8192

int main(int argc, char **argv)
{
    // argv[1] i tak zwraca null jak nie ma podanego pliku
    FILE *input = openFile(argv[1]);
    if (input == NULL)
    {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
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
    freeWordsMemory(ws, wordsToFindCount);
    fclose(input);

    return 0;
}