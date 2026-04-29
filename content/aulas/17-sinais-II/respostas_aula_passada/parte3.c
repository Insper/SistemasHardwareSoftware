//Envio de sinais em um programa¶
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
        while(1){
            printf("Meu pid = %d, estou em loop infinito\n",getpid());
            sleep(1);
        }
        
        int i = 1/0;
        printf("Divisão por zero!\n");
    }
    else{
        int status,pid_filho;
        //espera 10 segundos
        sleep(10);
        // manda um kill para o filho 
        kill(filho, SIGKILL);

        pid_filho = wait(&status);
        printf("Pid do meu filho = %d\n", pid_filho);
        printf("WIFEXITED = %d\n", WIFEXITED(status));
        printf("WIFSIGNALED =  %d\n", WIFSIGNALED(status));
        printf("WTERMSIG =  %d\n", WTERMSIG(status));
        printf("strsignal =  %s\n", strsignal(WTERMSIG(status)));
    }

    return 0;
}