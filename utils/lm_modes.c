#include "lm_modes.h"
#include "parser.h"
#include "lm_file.h"

char *builtin_repr[] = {
    "cd",
    "help",
    "quit",
    "history"};

int (*lm_builtins[])(char **, lm_context *) = {
    &lm_cd,
    &lm_help,
    &lm_quit,
    &lm_history,
};

int lm_bin_count()
{
    return sizeof(builtin_repr) / sizeof(char *);
}

void handleAllocationError(void *buffer)
{
    if (!buffer)
    {
        perror("LMSHELL: Allocation Error\n");
        exit(EXIT_FAILURE);
    }
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

void proc_start(char **argv, lm_context *context)
{
    pid_t pid, wpid;
    int status = -1;
    pid = fork();
    if (pid == 0)
    {
        if (execvp(argv[0], argv) < 0)
        {
            printf("encountered %s\n", argv[0]);
            perror("LMSHELL: Command not found ");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("LMSHELL: Subprocess cannot be created\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    context->l_com_status = status;
}

void proc_start_and_aware(char **argv, lm_context *context)
{
    if (context->l_com_status == 0)
    {
        proc_start(argv, context);
    }
}

void proc_start_or_aware(char **argv, lm_context *context)
{
    if (context->l_com_status != 0)
    {
        proc_start(argv, context);
    }
}

char *read_line()
{
    int buff_size = MAX_CMD;
    int position = 0;
    char *buffer = (char *)malloc(sizeof(char *) * buff_size);
    handleAllocationError(buffer);
    int c;
    while (1)
    {
        c = getchar();

        // handle terminating chars
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        // handle exceeding buffer size
        if (position >= buff_size)
        {
            buff_size += MAX_CMD;
            buffer = realloc(buffer, buff_size);
            handleAllocationError(buffer);
        }
    }
}

lm_mode parse_mode(int argc)
{
    return argc == 1;
}

char *print_mode(lm_mode mode)
{
    char *buffer = (char *)malloc(15);
    handleAllocationError(buffer);
    switch (mode)
    {
    case LM_BACH:
        snprintf(buffer, 15, "%s", "LM_BACH");
        break;

    default:
        snprintf(buffer, 15, "%s", "LM_INTERACTIVE");
        break;
    }
    return buffer;
}

void initialize_ctx(lm_context *context)
{
    char cwd[MAX_NAME * MAX_NAME];
    getcwd(cwd, sizeof(cwd));
    context->curr_path = cwd;
    context->l_com_status = 0;
    context->last_comm_op = LM_NONE;
    context->last_comm = "";
}

char *lm_prompt(lm_context *context)
{
    char *str_icmd = (char *)malloc(MAX_CMD);
    handleAllocationError(str_icmd);
    printf("[%s] %% ", context->curr_path);
    char *input = read_line();
    if (strcmp(input, ""))
    {
        context->last_comm = input;
        add_to_file("/tmp/.lmhistory", input);
        if (strstr(context->last_comm, "&&"))
        {
            context->last_comm_op = LM_AND;
        }
        else if (strstr(context->last_comm, "||"))
        {
            context->last_comm_op = LM_OR;
        }
        else if (strstr(context->last_comm, "|"))
        {
            context->last_comm_op = LM_PIPE;
        }
        else if (strstr(context->last_comm, ";"))
        {
            context->last_comm_op = LM_IGN;
        }
        else if (strstr(context->last_comm, "#"))
        {
            context->last_comm_op = LM_COMMENT;
        }
        else if (strstr(context->last_comm, ">"))
        {
            context->last_comm_op = LM_REDIRECT;
        }
        else if (strstr(context->last_comm, ">>"))
        {
            context->last_comm_op = LM_APPEND;
        }
        else if (strstr(context->last_comm, ">>"))
        {
            context->last_comm_op = LM_APPEND;
        }
        else
        {
            context->last_comm_op = LM_NONE;
        }
    }
    else
    {
        context->last_comm = "";
        context->last_comm_op = LM_NONE;
    }
    return context->last_comm;
}

char *lm_virt_prompt(lm_context *context, char *line)
{
    resetCtx(context);
    char *str_icmd = (char *)malloc(MAX_CMD);
    handleAllocationError(str_icmd);
    if (strcmp(line, ""))
    {
        context->last_comm = line;
        add_to_file("/tmp/.lmhistory", line);
        if (strstr(line, "&&"))
        {
            context->last_comm_op = LM_AND;
        }
        else if (strstr(line, "||"))
        {
            context->last_comm_op = LM_OR;
        }
        else if (strstr(line, "|"))
        {
            context->last_comm_op = LM_PIPE;
        }
        else if (strstr(line, ";"))
        {
            context->last_comm_op = LM_IGN;
        }
        else if (strstr(line, "#"))
        {
            context->last_comm_op = LM_COMMENT;
        }
        else if (strstr(line, ">"))
        {
            context->last_comm_op = LM_REDIRECT;
        }
        else if (strstr(line, ">>"))
        {
            context->last_comm_op = LM_APPEND;
        }
        else if (strstr(line, ">>"))
        {
            context->last_comm_op = LM_APPEND;
        }
        
    }
    else
    {
        context->last_comm = "";
        context->last_comm_op = LM_NONE;
    }
    printf("Last command operator %d\n", context->last_comm_op);
    return context->last_comm;
}

void lm_cleanup(lm_context *context)
{
    free(context);
}

void resetCtx(lm_context *context)
{
    context->last_comm = "";
    context->last_comm_op = LM_NONE;
}

void lm_trim(char *string)
{
    int i, j;

    for (i = 0; string[i] == ' ' || string[i] == '\t'; i++)
        ;

    for (j = 0; string[i]; i++)
    {
        string[j++] = string[i];
    }
    string[j] = '\0';
    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] != ' ' && string[i] != '\t')
            j = i;
    }
    string[j + 1] = '\0';
}

void proc_start_pipe(char **cmd1, char **cmd2)
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("LMSHELL: Pipe Error");
        exit(1);
    }

    if (fork() == 0)
    {
        close(STDOUT_FILENO);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        execvp(cmd1[0], cmd1);
        perror("LMSHELL: Execvp Error");
        exit(1);
    }
    if (fork() == 0)
    {
        close(STDIN_FILENO);
        dup(fd[0]);
        close(fd[1]);
        close(fd[0]);
        execvp(cmd2[0], cmd2);
        perror("LMSHELL: Execvp Error");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(0);
    wait(0);
}
void proc_start_redirect(char **cmd1, char **cmd2)
{
    // todo, remove file workaround
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("LMSHELL: Fork failed\n");
    }
    else if (pid == 0)
    {
        int f;

        if ((f = creat(cmd2[0], S_IRUSR | S_IWUSR)) < 0)
            perror("creat() error");
        else
        {
            write(f, "", strlen(""));
            close(f);
            unlink(cmd2[0]);
        }

        int redirect_flag = 0;
        FILE *fstream;
        fstream = fopen(cmd2[0], "w+");
        if (fstream == NULL)
        {
            perror("LMSHELL:failed to open file");
        }
        freopen(cmd2[0], "w", stdout);
        if (execvp(cmd1[0], cmd1) < 0)
        {
            perror("failed to open file");
        }
        printf("ran successfully");
        fclose(stdout);
        fclose(fstream);
    }
}

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
                //printf("Last operator %d", (int)ctx->last_comm_op);
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
        //if (line)
        //    free(line);
    }
}