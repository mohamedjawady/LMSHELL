#include "lm_modes.h"
#include "parser.h"
#include "lm_builtins.h"
#include "lm_process.h"
#include "constants.h"

#ifndef LM_WRAPPER
#define LM_WRAPPER

// wraps prompt line execution
void lm_command_wrapper_interactive(lm_context *ctx);

// wraps batch mode
void lm_command_wrapper_batch(lm_context *ctx, char *filename);

#endif