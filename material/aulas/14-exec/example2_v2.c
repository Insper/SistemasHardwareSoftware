#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t filho_pid;
    pid_t pai_pid;
    pid_t meu_pid;

    for (int i=0; i<8; i++) {
        filho_pid = fork();

        if (filho_pid == 0) {
            meu_pid = getpid();
            pai_pid = getppid();
            printf("Eu sou o processo filho, pid=%d, ppid=%d, meu id do programa é %d\n", meu_pid, pai_pid, i+1);
            return 0;
        } else if (i==0) {
            meu_pid = getpid();
            printf("Eu sou o processo pai, pid=%d, meu id do programa é %d\n", meu_pid, i+1);
        }
    }

    return 0;
}