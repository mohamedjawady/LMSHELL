#include <stdio.h>
#include <signal.h>
#include "lm_modes.h"

int main(int argc, char **argv)
{
    lm_mode mode = parse_mode(argc);
    if (mode)
    {
        // INTERACTIVE MODE
        lm_context *ctx = (lm_context*)malloc(sizeof(lm_context));
        initialize_ctx(ctx);
        lm_command_wrapper(ctx);
        lm_cleanup(ctx);
    }
    else
    {
        // BACH MODE
        printf("BACH mode\n");
    }
    
}