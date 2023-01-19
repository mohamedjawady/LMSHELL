#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "lm_modes.h"
#include "constants.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef LM_PROCESS
#define LM_PROCESS

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

#endif