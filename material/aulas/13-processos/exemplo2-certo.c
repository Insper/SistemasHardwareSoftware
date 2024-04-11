#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t filho;

    filho = fork();

    if (filho == 0) {
        
        sleep(1);
        printf("Acabei filho\n");
        return 10;
    } else {
        int status;
        printf("Esperando o filho acabar!\n");
        wait(&status);
        if(WIFEXITED(status)){
            printf("terminou normalmente, com o retorno %d \n",WEXITSTATUS(status));
        }
        else 
            printf("nao terminou normalmente.\n");
    }
    return 0;
}
