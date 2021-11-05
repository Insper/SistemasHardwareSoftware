// Abra o terminal e execute o executavel deste codigo
// Abra outro terminal e chame
// kill -s SIGKILL <pid_filho>
// e veja o que acontece

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("Sou o processo filho, meu pid eh %d\n", getpid());
        while(1);
    } else {
        
        printf("O pid do filho é %d\n", filho);
        pid_t pid_terminou;
        int ws;

        pid_terminou = wait(&ws);

        printf("O meu filho de PID %d terminou!\n", pid_terminou);
        printf("Algumas infos sobre a finalizacao do processo filho:\n");
        printf("EXIT %d\nSIGNALED %d\nSIGTERM %d\n", WIFEXITED(ws), WIFSIGNALED(ws), WTERMSIG(ws));
        printf("Sinal recebido pelo filho: %s\n", strsignal(WTERMSIG(ws)));
    }

    return 0;
}