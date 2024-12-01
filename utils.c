#include "utils.h"

#define BUFSIZE 1024

FILE *openFile(char *filename)
{
    return filename != NULL ? fopen(filename, "r") : stdin;
}

// TODO: co robić jak jedno słowo występuje kilka razy w jednej linii?
void checkWords(FILE *file, wordsStorage_t *storage, int wordsCount)
{
    // linia moze wykraczac poza BUFSIZE,
    // bo robimy line++ tylko jak jest \n na koncu
    // tak powinno być optymalniej niż robienie malloc(fileSize)
    // bo co jak plik ma 100 GB?
    char *buf = (char *)malloc(BUFSIZE);
    int line = 1;
    while (fgets(buf, BUFSIZE, file) != NULL)
    {
        /**
         * uzywamy strlen() bo nie wiemy jaki rzeczywisty rozmiar
         * linijki został wczytany
         */
        int readLen = strlen(buf);
        char lastChar = buf[readLen - 1];

        /**
         * tokenizujemy linijke po spacji i tabach
         * i sprawdzamy czy slowo jest w naszej tablicy
         * jesli tak to dodajemy numer linijki
         * dla tablicy tego slowa
         */
        char *lastTokenPtr;
        char *token = strtok_r(buf, " \t", &lastTokenPtr);
        while (token != NULL)
        {
            for (int i = 0; i < wordsCount; i++)
            {
                if (strcmp(token, storage[i]->word) == 0)
                {
                    storage[i]->lines[storage[i]->linesCount] = line;
                    storage[i]->linesCount += 1;
                }
            }
            token = strtok_r(NULL, " \t", &lastTokenPtr);
        }

        /**
         * strtok() zmienia bufor, wiec musimy sprawdzic
         * czy nie ma \n na koncu przed podzieleniem na tokeny
         */
        if (lastChar == '\n')
            line++;
    }

    // zwalniamy bufor po skonczeniu
    free(buf);
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
