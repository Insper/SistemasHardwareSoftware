#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio

int main() {
    int status;
    pid_t filho;
    
    filho = fork();
    if (filho == 0) {
        printf("pid do filho: %d\n", getpid());
        while (1);
    }
    
    wait(&status);
    
    if (WIFSIGNALED(status)) {
        printf("Sinal: %d\n", WTERMSIG(status));
    }
    
    return 0;
}
