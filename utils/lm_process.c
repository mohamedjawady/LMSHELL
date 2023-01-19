#include "lm_process.h"

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
