#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        int pid_processo = getpid();
        printf("processo filho pid=%d está em loop infinito !!\n",pid_processo);
        // entra em loop infinito
        while(1);
    }
    else{
        int status, pid_filho;
        // pai espera 10 segundos e manda kill para o filho
        sleep(10);
        // kill(filho, SIGKILL); // descomentar aqui para testar kill pelo terminal
        pid_filho = wait(&status);
        printf("filho terminou pid=%d status=%d\n",pid_filho,status);
        printf("IFEXITED = %d\n",WIFEXITED(status));
        printf("WIFSIGNALED = %d\n",WIFSIGNALED(status));
        printf("WTERMSIG = %d\n",WTERMSIG(status));
        printf("strsignal = %s\n",strsignal(WTERMSIG(status)));
    }

    return 0;
}
