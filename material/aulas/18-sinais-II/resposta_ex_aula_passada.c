#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Meu pid: %d\n", getpid());
        while(1);
    }

    int ws;

    sleep(10);
    int wait_return = waitpid(filho, &ws, WNOHANG);
    printf("wait_return: %d\n", wait_return);

    if (wait_return == 0) {
        printf("Ainda nao terminou, vou chamar kill!\n");
        kill(filho, SIGKILL);
        wait(&ws);
    } else {
        printf("O processo filho já finalizou!\n");
    }

    printf("EXITED %d \n"
           "SIGNALED %d \n"
           "TERMSIG %d\n"
           "Error: %s\n",
           WIFEXITED(ws), 
           WIFSIGNALED(ws),
           WTERMSIG(ws), 
           strsignal(WTERMSIG(ws)));

    return 0;
}
