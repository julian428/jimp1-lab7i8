#include "utils.h"

FILE *openFile(char *filename)
{
    return filename != NULL ? fopen(filename, "r") : stdin;
}

int checkWords(char *source, char *word)
{
    return strstr(source, word) != NULL;
}

void printLines(wordsStorage_t *storage, int wordsStorageCount, FILE *output)
{
    for (int i = 0; i < wordsStorageCount; i++)
    {
        fprintf(output, "%s: ", storage[i]->word);
        for (int j = 0; j < storage[i]->linesCount; j++)
        {
            fprintf(output, "%d ", storage[i]->lines[j]);
        }
        fprintf(output, "\n");
    }
}

void freeWordsMemory(wordsStorage_t *ws, int wordsCount)
{
    for (int i = 0; i < wordsCount; i++)
    {
        free(ws[i]);
    }
    free(ws);
}
