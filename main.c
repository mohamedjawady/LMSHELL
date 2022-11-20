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

        // testing block start
        char **testing = {"ls", ".", NULL};
        int ret = proc_start(testing);
        printf("%d\n", ret);
        // testing block end

        while (strcmp(ctx.last_comm, "quit"))
        {
            // INTERACTIVE LOOP
            printf("> Last command %s\n", lm_prompt(&ctx));
        }
    }
    else
    {
        // BACH MODE
        printf("BACH mode\n");
    }

    lm_cleanup();
}