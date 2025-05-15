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
        int wait_return = waitpid(filho, &status, WNOHANG);
        printf("wait_return: %d\n", wait_return);
        //se retornou 0 o filho não encerrou 
        if (wait_return == 0) {
            printf("Ainda nao terminou, vou chamar kill!\n");
            kill(filho, SIGKILL);
            wait(&status);
        } else {
            printf("O processo filho já finalizou!\n");
        }
        printf("filho terminou pid=%d status=%d\n",filho,status);
        printf("IFEXITED = %d\n",WIFEXITED(status));
        printf("WIFSIGNALED = %d\n",WIFSIGNALED(status));
        printf("WTERMSIG = %d\n",WTERMSIG(status));
        printf("strsignal = %s\n",strsignal(WTERMSIG(status)));
    }

    return 0;
}