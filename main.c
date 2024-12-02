#include <stdio.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <file> <sort> <word1> <word2> ... <wordN>\n", argv[0]);
        return 1;
    }

    FILE *input = openFile(argv[1]);

    if (input == NULL)
    {
        fprintf(stderr, "Error: cannot open file\n");
        return 1;
    }

    int wordsToFindCount = argc - 3;

    wordsStorage_t *ws = newWordsStorage(wordsToFindCount, argv + 3);

    checkWords(input, ws, wordsToFindCount);

    int sortResults = atoi(argv[2]);

    printLines(ws, wordsToFindCount, stdout, sortResults);
    freeWordsMemory(ws, wordsToFindCount);
    fclose(input);

    return 0;
}