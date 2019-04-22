#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pai, filho;
    int variavel = 5;

    printf("Eu sou o processo pai: %d\n", getpid());
    
    for (int i = 0; i < 7; i++) {
        if (fork() == 0) {
            printf("Eu sou um processo filho: %d, meu pai eh %d, meu id eh %d\n", getpid(), getppid(), i);
            return 1;
        }
    }
    
    return 0;
}
