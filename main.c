#include <stdio.h>
#include <signal.h>
#include "lm_modes.h"
#include "parser.h"
int main(int argc, char **argv)
{
    lm_mode mode = parse_mode(argc);
    if (mode)
    {
        // INTERACTIVE MODE
        lm_context ctx;
        initialize_ctx(&ctx);

        lm_help((char **)NULL, &ctx);

        while (1)
        {
            // REPL LOOP

            if (!strcmp(ctx.last_comm, "quit"))
            {
                lm_quit((char **)NULL, &ctx);
                resetCtx(&ctx);
                continue;
            }
            else if (!strcmp(ctx.last_comm, "help"))
            {
                lm_help((char **)NULL, &ctx);
                resetCtx(&ctx);
                continue;
            }
            if (strcmp(ctx.last_comm, ""))
            {
                char **array_string;
                int size;
                char **cmd1;
                char **cmd2;
                switch ((int)ctx.last_comm_op)
                {
                case LM_AND:
                    split_string_subs(ctx.last_comm, "&&", array_string);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    proc_start(cmd1, &ctx);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start_and_aware(cmd2, &ctx);

                    break;
                case LM_OR:
                    split_string_subs(ctx.last_comm, "||", array_string);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    proc_start(cmd1, &ctx);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start_or_aware(cmd2, &ctx);
                    break;
                case LM_PIPE:
                    split_string_subs(ctx.last_comm, "|", array_string);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start_pipe(cmd1, cmd2);
                    break;
                case LM_IGN:
                    string_split(ctx.last_comm, ';', &array_string, &size);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    proc_start(cmd1, &ctx);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start(cmd2, &ctx);
                    break;
                case LM_NONE:
                    lm_trim(ctx.last_comm);
                    string_split(ctx.last_comm, ' ', &array_string, &size);
                    if (!strcmp(array_string[0], "cd"))
                    {
                        lm_cd(array_string, &ctx);
                        resetCtx(&ctx);
                        continue;
                    }
                    else
                    {
                        proc_start(array_string, &ctx);
                    }
                    break;
                }
            }
            lm_prompt(&ctx);
        }
    }
    else
    {
        // BACH MODE
        printf("BACH mode\n");
    }

    lm_cleanup();
}