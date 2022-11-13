#include <stdio.h>
#include <unistd.h>

int main() {
    printf("[+] Testing fork syscall, PID: %d, PPID: %d\n", getpid(), getppid());
    if(fork() == 0) {
        // child block
        pid_t pid = getpid();
        pid_t ppid = getppid();
        printf("-> Child Running: PID %d, PPID: %d\n", pid, ppid); // ppid is wrong because by the time child runs the parent finished, being reassigned.
    }else{
        // parent block
        pid_t pid = getpid();
        pid_t ppid = getppid();
        printf("-> Parent Running: PID %d, PPID: %d\n", pid, ppid);
    }
    return 0;
}