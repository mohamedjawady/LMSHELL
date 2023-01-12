#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
        int des_p[2];
        if(pipe(des_p) == -1) {
          perror("lm - pipe failed");
          exit(1);
        }

	// ch1
        if(fork() == 0)            
        {
            close(STDOUT_FILENO);  
            dup(des_p[1]);          
            close(des_p[0]);       
            close(des_p[1]);

            const char* cmd1[] = { "ls", "-l", 0};
            execvp(cmd1[0], cmd1);
            perror("execvp of ls failed");
            exit(1);
        }
	// ch2
        if(fork() == 0)            
        {
            close(STDIN_FILENO);   
            dup(des_p[0]);         
            close(des_p[1]);       
            close(des_p[0]);

            const char* cmd2[] = { "wc", "-l", 0};
            execvp(cmd2[0], cmd2);
            perror("execvp of wc failed");
            exit(1);
        }

        close(des_p[0]);
        close(des_p[1]);
        wait(0);
        wait(0);
        return 0;
}
