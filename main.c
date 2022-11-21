#include <stdio.h>
#include <signal.h>
#include "lm_modes.h"
int main(int argc, char **argv)
{
    lm_mode mode = parse_mode(argc);
    if (mode)
    {
        // INTERACTIVE MODE
        lm_context ctx;
        initialize_ctx(&ctx);

        // testing block:help start
        lm_help((char **)NULL, &ctx);
        // testing block:help end

        // testing block:cd start
        char **cdArgs[][MAX_NAME] = {"cd", "./utils"};
        lm_cd(cdArgs, &ctx);
        // testing block:cd end

        while (1)
        {
            // REPL LOOP
            printf("> Last command %s\n", lm_prompt(&ctx));
            if (!strcmp(ctx.last_comm, "quit"))
            {
                break;
            }
        }
    }
    else
    {
        // BACH MODE
        printf("BACH mode\n");
    }

    lm_cleanup();
}