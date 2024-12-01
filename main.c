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

    wordsStorage_t *ws = newWordsStorage(wordsToFindCount, argv + 2);

    checkWords(input, ws, wordsToFindCount);

    printLines(ws, wordsToFindCount, stdout);
    freeWordsMemory(ws, wordsToFindCount);
    fclose(input);

    return 0;
}