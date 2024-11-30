#include "utils.h"

FILE *openFile(char *filename, long *fileSize)
{
    FILE *file = filename != NULL ? fopen(filename, "r") : stdin;
    if (filename == NULL)
        return file;

    // Move to the end of the file
    fseek(file, 0, SEEK_END);

    // Get the file size
    *fileSize = ftell(file);
    if (*fileSize == -1)
        return NULL;

    // Return to the beginning of the file
    rewind(file);

    return file;
}

void checkWords(FILE *file, long fileSize, wordsStorage_t *storage, int wordsCount)
{

    char *buf = (char *)malloc(fileSize);
    for (int line = 1; fgets(buf, fileSize, file) != NULL; line++)
    {
        for (int i = 0; i < wordsCount; i++)
        {
            if (strstr(buf, storage[i]->word))
            {
                storage[i]->lines[storage[i]->linesCount] = line;
                storage[i]->linesCount += 1;
            }
        }
    }
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
