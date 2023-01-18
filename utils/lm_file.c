#include "lm_file.h"
#include <stdlib.h>
#include <stdio.h>

void open_file_lbl(char *filename)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 1;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("LMSHELL: Failed to open file");
    }
    else
    {
        while ((read = getline(&line, &len, fp)) != -1)
        {
            printf("%d- %s", i, line);
            i++;
        }

        fclose(fp);
        if (line)
            free(line);
    }
}

void add_to_file(char *fname, char *line)
{
    FILE *pFile;

    pFile = fopen(fname, "a");
    if (pFile == NULL)
    {
        perror("LMSHELL: Error opening file.");
    }
    else
    {
        fprintf(pFile, "%s\n", line);
    }
    fclose(pFile);
}