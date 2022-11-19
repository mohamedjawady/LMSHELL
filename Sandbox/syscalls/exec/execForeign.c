#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    pid_t pid = getpid();
    printf("Foreign executable, PID: %ld\n", pid);
    printf("Running with arguments:\n");
    for(int i=0; i<argc; i++){
        printf("[%d] %s\n", i, argv[i]);
    }
}