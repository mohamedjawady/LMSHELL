#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void intHandler(int sigNum){
    printf("exiting...\n");
    
}

int main(int argc, char** argv){
    pid_t ch_pid;
    int status;
    if (fork() == 0){
        while(1){
            printf("Child is running ...\n");
            sleep(2);
        };
        exit(0);
    }else {
        signal(SIGINT, intHandler);
        ch_pid = wait(&status);
        printf("|-[Parent:%d]\n", getpid());
        printf("--> [Child:%d] WAIT returned [Status:%d]\n", ch_pid, status);

        // tests of the status of the child process
        printf("  |-> [WIFEXITED]    %d\n", WIFEXITED(status));
        printf("  |-> [WEXITSTATUS]  %d\n", WEXITSTATUS(status));
        printf("  |-> [WIFSIGNALED]  %d\n", WIFSIGNALED(status));
        printf("  --> [WTERMSIG]     %d\n", WTERMSIG(status));
    }
}