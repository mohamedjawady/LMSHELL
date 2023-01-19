#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "constants.h"

#ifndef LM_MODES
#define LM_MODES

// mode type
typedef enum
{
    LM_INTERACTIVE = 1,
    LM_BACH = 0
} lm_mode;

// command operators
typedef enum
{
    LM_NONE,
    LM_AND,
    LM_OR,
    LM_IGN,
    LM_PIPE,
    LM_COMMENT,
    LM_REDIRECT,
    LM_APPEND
} ops;

// context type
typedef struct
{
    char *curr_path;
    char *last_comm;
    ops last_comm_op;
    int l_com_status;
    char *last_sdout;
    char *last_sterr;
} lm_context;


// handles memory allocation errors
void handleAllocationError(void *buffer);

// Determine mode of execution given the count of arguments.
lm_mode parse_mode(int argc);

// Show the mode of execution.
char *print_mode(lm_mode mode);

// Construct str_path and display prompt
char *lm_prompt(lm_context *context);

// lm_prompt simulation for batch mode 
char *lm_virt_prompt(lm_context *context, char *line);

// Initialize context struct for interactive mode
void initialize_ctx(lm_context *context);

// Read from stdin
char *read_line();

// Exit and cleanup
void lm_cleanup(lm_context *context);

// resets context
void resetCtx(lm_context *context);


#endif