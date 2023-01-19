#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#ifndef LM_FILE
#define LM_file

// open file and read from it line by line
void open_file_lbl(char *filename);

// append string to end of text file
void add_to_file(char *fname, char *line);

#endif