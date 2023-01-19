#include "lm_wrappers.h"
void lm_command_wrapper_interactive(lm_context *ctx)
{
    while (1)
    {
        if (!strcmp(ctx->last_comm, "quit"))
        {
            lm_quit((char **)NULL, ctx);
            resetCtx(ctx);
            continue;
        }
        else if (!strcmp(ctx->last_comm, "help"))
        {
            lm_help((char **)NULL, ctx);
            resetCtx(ctx);
            continue;
        }
        else if (!strcmp(ctx->last_comm, "history"))
        {
            lm_history((char **)NULL, ctx);
            resetCtx(ctx);
            continue;
        }
        if (strcmp(ctx->last_comm, ""))
        {
            char **array_string;
            int size;
            char **cmd1 = (char **)malloc(MAX_CMD);
            char **cmd2 = (char **)malloc(MAX_CMD);
            switch ((int)ctx->last_comm_op)
            {
            case LM_AND:
                split_string_subs(ctx->last_comm, "&&", array_string);
                lm_trim(array_string[0]);
                string_split(array_string[0], ' ', &cmd1, &size);
                proc_start(cmd1, ctx);
                lm_trim(array_string[1]);
                string_split(array_string[1], ' ', &cmd2, &size);
                proc_start_and_aware(cmd2, ctx);
                break;
            case LM_OR:
                split_string_subs(ctx->last_comm, "||", array_string);
                lm_trim(array_string[0]);
                string_split(array_string[0], ' ', &cmd1, &size);
                proc_start(cmd1, ctx);
                lm_trim(array_string[1]);
                string_split(array_string[1], ' ', &cmd2, &size);
                proc_start_or_aware(cmd2, ctx);
                break;
            case LM_PIPE:
                split_string_subs(ctx->last_comm, "|", array_string);
                lm_trim(array_string[0]);
                string_split(array_string[0], ' ', &cmd1, &size);
                lm_trim(array_string[1]);
                string_split(array_string[1], ' ', &cmd2, &size);
                proc_start_pipe(cmd1, cmd2);
                break;
            case LM_IGN:
                string_split(ctx->last_comm, ';', &array_string, &size);
                lm_trim(array_string[0]);
                string_split(array_string[0], ' ', &cmd1, &size);
                proc_start(cmd1, ctx);
                lm_trim(array_string[1]);
                string_split(array_string[1], ' ', &cmd2, &size);
                proc_start(cmd2, ctx);
                break;
            case LM_REDIRECT:
                // cmd 2 is used here to store the redirect target at cmd2[0]
                split_string_subs(ctx->last_comm, ">", array_string);
                lm_trim(array_string[0]);
                string_split(array_string[0], ' ', &cmd1, &size);
                lm_trim(array_string[1]);
                string_split(array_string[1], ' ', &cmd2, &size);
                proc_start_redirect(cmd1, cmd2);
                break;
            case LM_COMMENT:
                // do nothing
                break;
            case LM_NONE:
                lm_trim(ctx->last_comm);
                string_split(ctx->last_comm, ' ', &array_string, &size);
                if (!strcmp(array_string[0], "cd"))
                {
                    lm_cd(array_string, ctx);
                    resetCtx(ctx);
                    continue;
                }
                else
                {
                    proc_start(array_string, ctx);
                }
                break;
            }
            free(cmd1);
            free(cmd2);
        }
        lm_prompt(ctx);
    }
}

void lm_command_wrapper_batch(lm_context *ctx, char *filename)
{

    FILE *script;
    char line[MAX_CMD];
    size_t len = 0;
    char* read;
    int i = 1;
    script = fopen(filename, "r");
    if (script == NULL)
    {
        perror("LMSHELL: Failed to open script file");
    }
    else
    {
        while (fgets(line, MAX_CMD, script) != NULL)
        {
            resetCtx(ctx);
            line[strcspn(line, "\n")] = 0;
            lm_virt_prompt(ctx, line);
            
            //printf("inputted %s at lvl wrapper", line);
            
            if (!strcmp(line, "quit"))
            {
                lm_quit((char **)NULL, ctx);
                //resetCtx(ctx);
                continue;
            }
            else if (!strcmp(line, "help"))
            {
                lm_help((char **)NULL, ctx);
                //resetCtx(ctx);
                continue;
            }
            else if (!strcmp(line, "history"))
            {
                lm_history((char **)NULL, ctx);
                //resetCtx(ctx);
                continue;
            }
            if (strcmp(line, ""))
            {
                char **array_string;
                int size;
                char **cmd1 = (char **)malloc(MAX_CMD);
                char **cmd2 = (char **)malloc(MAX_CMD);
                
                switch ((int)ctx->last_comm_op)
                {
                case LM_AND:
                    split_string_subs(line, "&&", array_string);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    proc_start(cmd1, ctx);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start_and_aware(cmd2, ctx);
                    break;
                case LM_OR:
                    split_string_subs(line, "||", array_string);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    proc_start(cmd1, ctx);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start_or_aware(cmd2, ctx);
                    break;
                case LM_PIPE:
                    split_string_subs(line, "|", array_string);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start_pipe(cmd1, cmd2);
                    break;
                case LM_IGN:
                    string_split(line, ';', &array_string, &size);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    proc_start(cmd1, ctx);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start(cmd2, ctx);
                    break;
                case LM_REDIRECT:
                    // cmd 2 is used here to store the redirect target at cmd2[0]
                    string_split(line, '>', &array_string, &size);
                    lm_trim(array_string[0]);
                    string_split(array_string[0], ' ', &cmd1, &size);
                    lm_trim(array_string[1]);
                    string_split(array_string[1], ' ', &cmd2, &size);
                    proc_start_redirect(cmd1, cmd2);
                    break;
                case LM_COMMENT:
                    // do nothing
                    break;
                case LM_NONE:
                    lm_trim(line);
                    string_split(line, ' ', &array_string, &size);
                    if (!strcmp(array_string[0], "cd"))
                    {
                        lm_cd(array_string, ctx);
                        //resetCtx(ctx);
                        continue;
                    }
                    else
                    {
                        proc_start(array_string, ctx);
                    }
                    break;
                }
                
                free(cmd1);
                free(cmd2);
            }
            
            i++;
        }

        fclose(script);
    }
}
