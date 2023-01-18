#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef LM_MODES
#define LM_MODES

#define MAX_CMD 1024
#define MAX_NAME 255

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

// cd built_in
int lm_cd(char **args, lm_context *context);

// help built_in
int lm_help(char **args, lm_context *context);

// quit built_in
int lm_quit(char **args, lm_context *context);

// history built_in
int lm_history(char **args, lm_context *context);

// Exec a child process
void proc_start(char **argv, lm_context *context);

// Run second command if previous command ran succefully
void proc_start_and_aware(char **argv, lm_context *context);

// Run second command if previous command failed
void proc_start_or_aware(char **argv, lm_context *context);

// Run two commands separated by pipe
void proc_start_pipe(char **cmd1, char **cmd2);

// Redirect Stdout of cmd1 to cmd2[0]
void proc_start_redirect(char **cmd1, char **cmd2);

// Count of built-in commmands
int lm_bin_count();

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

// trims strings leading and terminating whitespace
void lm_trim(char *string);

// wraps prompt line execution
void lm_command_wrapper_interactive(lm_context *ctx);

// wraps batch mode
void lm_command_wrapper_batch(lm_context *ctx, char *filename);
#endif