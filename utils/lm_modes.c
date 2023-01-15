#include "lm_modes.h"

char *builtin_repr[] = {
    "cd",
    "help",
    "quit",
};

int (*lm_builtins[])(char **, lm_context *) = {
    &lm_cd,
    &lm_help,
    &lm_quit};

int lm_bin_count()
{
    return sizeof(builtin_repr) / sizeof(char *);
}

int lm_cd(char **args, lm_context *context)
{
    if (args[1] == NULL)
    {
        perror("LMSHELL: cd - Argument not supplied\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror(sprintf("LMSHELL: cd - Cannot change directory to %s\n", args[1]));
        }
        else
        {
            char *cwd = (char *)malloc(1024);
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
        if (execvp(argv[0], argv) == -1)
        {
            perror("LMSHELL: Command not found\n");
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
    context->l_com_status = status ;
}

void proc_start_and_aware(char **argv, lm_context *context){
    if(context->l_com_status==0){
        proc_start(argv, context);
    }
}

void proc_start_or_aware(char **argv, lm_context *context){
    if(context->l_com_status!=0){
        proc_start(argv, context);
    }
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
    printf("[%s] %% ", context->curr_path);
    char *input = read_line();
    if (strcmp(input, ""))
    {
        context->last_comm = input;
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

void lm_cleanup()
{
    printf("LMSHELL: Exited\n");
}

void resetCtx(lm_context *context)
{
    context->last_comm = "";
    context->last_comm_op = LM_NONE;
    
}

void lm_trim(char *string)
{
	int i,j;
 
	for(i=0;string[i]==' '||string[i]=='\t';i++);
		
	for(j=0;string[i];i++)
	{
		string[j++]=string[i];
	}
	string[j]='\0';
	for(i=0;string[i]!='\0';i++)
	{
		if(string[i]!=' '&& string[i]!='\t')
				j=i;
	}
	string[j+1]='\0';
}