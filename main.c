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

    int wordsToFindCount = argc - 3;

    wordsStorage_t *ws = newWordsStorage(wordsToFindCount, argv + 3);

    checkWords(input, ws, wordsToFindCount);

    int sortResults = argc > 2 && atoi(argv[2]);

    printLines(ws, wordsToFindCount, stdout, sortResults);
    freeWordsMemory(ws, wordsToFindCount);
    fclose(input);

    return 0;
}