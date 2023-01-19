#include "lm_modes.h"
#include "lm_file.h"
#include "constants.h"

#ifndef LM_BUILTINS
#define LM_BUILTINS

// cd built_in
int lm_cd(char **args, lm_context *context);

// help built_in
int lm_help(char **args, lm_context *context);

// quit built_in
int lm_quit(char **args, lm_context *context);

// history built_in
int lm_history(char **args, lm_context *context);

// Count of built-in commmands
int lm_bin_count();

#endif