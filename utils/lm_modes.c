#include "lm_modes.h"

int proc_start(char **argv)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(argv[0], argv) == -1)
        {
            perror("LMSHELL: Subprocess cannot start\n");
        }
        exit(EXIT_FAILURE);
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
    return 1;
}

void handleAllocationError(void *buffer)
{
    if (!buffer)
    {
        perror("LMSHELL: Allocation Error\n");
        exit(EXIT_FAILURE);
    }
}

char *read_line()
{
    int buff_size = MAX_CMD;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buff_size);
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
    context->last_comm = "";
}

char *lm_prompt(lm_context *context)
{
    char *str_icmd = (char *)malloc(MAX_CMD);
    printf("[%s] %% ", context->curr_path);
    context->last_comm = read_line();
    return context->last_comm;
}

void lm_cleanup()
{
    printf("LMSHELL: Exited\n");
}