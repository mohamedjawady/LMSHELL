#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef LM_MODES
#define LM_MODES

#define MAX_CMD 255
#define MAX_NAME 255

typedef enum
{
    LM_INTERACTIVE = 1,
    LM_BACH = 0
} lm_mode;

typedef struct
{
    char *curr_path;
    char *last_comm;
    unsigned l_com_status;
} lm_context;

// Exec a child process
int proc_start(char **argv);

// Determine mode of execution given the count of arguments.
lm_mode parse_mode(int argc);

// Show the mode of execution.
char *print_mode(lm_mode mode);

// Construct str_path and display prompt
char *lm_prompt(lm_context *context);

// Initialize context struct for interactive mode
void initialize_ctx(lm_context *context);

// Read from stdin
char *read_line();

// Exit and cleanup
void lm_cleanup();

#endif