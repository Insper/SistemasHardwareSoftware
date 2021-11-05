#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) { //este bloco executa apenas no filho
        int i = 1/0;
        printf("Divisão por zero!\n");
    } else { // este bloco executa apenas no pai        
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