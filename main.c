#include "utils/lm_modes.h"
#include "utils/lm_wrappers.h"

int main(int argc, char **argv)
{
    lm_mode mode = parse_mode(argc);
    if (mode)
    {
        // INTERACTIVE MODE
        lm_context *ctx = (lm_context*)malloc(sizeof(lm_context));
        initialize_ctx(ctx);
        lm_command_wrapper_interactive(ctx);
        lm_cleanup(ctx);
    }
    else
    {
        // BACH MODE
        lm_context *ctx = (lm_context*)malloc(sizeof(lm_context));
        initialize_ctx(ctx);
        lm_command_wrapper_batch(ctx, argv[1]);
        lm_cleanup(ctx);
    }
    
}