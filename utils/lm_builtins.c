#include "lm_builtins.h"
char *builtin_repr[] = {
    "cd",
    "help",
    "quit",
    "history"};


int lm_bin_count()
{
    return sizeof(builtin_repr) / sizeof(char *);
}


int lm_cd(char **args, lm_context *context)
{
    if (args[1] == NULL)
    {
        if (chdir("//") != 0)
        {
            perror("LMSHELL: cd - Cannot change directory to root\n");
        }
        else
        {
            char *cwd = (char *)malloc(1024);
            handleAllocationError(cwd);
            getcwd(cwd, 1024);
            context->curr_path = cwd;
            return 0;
        }
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("LMSHELL: cd - Cannot change directory");
        }
        else
        {
            char *cwd = (char *)malloc(1024);
            handleAllocationError(cwd);
            getcwd(cwd, 1024);
            context->curr_path = cwd;
            return 0;
        }
    }
    return 1;
}

int lm_quit(char **args, lm_context *context)
{
    exit(0);
    return 0;
}

int lm_history(char **args, lm_context *context)
{
    // todo: load config and set history path
    open_file_lbl("/tmp/.lmhistory");
    return 0;
}

int lm_help(char **args, lm_context *context)
{
    int i;
    printf("LMSHELL - Lightweight Linux Shell\n");
    printf("Built-in commands:\n");

    for (i = 0; i < lm_bin_count(); i++)
    {
        printf("  %s\n", builtin_repr[i]);
    }
    return 1;
}
