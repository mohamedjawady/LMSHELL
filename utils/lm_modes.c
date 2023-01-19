#include "lm_modes.h"
#include "parser.h"
#include "lm_file.h"
#include "constants.h"

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

