#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pai, filho;
    int variavel = 5;

    filho = fork();
    if (filho == 0) {
        // processo filho aqui
        pai = getppid();
        filho = getpid();
        variavel *= 2;
        printf("eu sou o processo filho %d, meu pai é %d\nvariavel %d\n", 
            filho, pai, variavel);
    } else {
        // processo pai aqui!
        pai = getpid();
        printf("eu sou o processo pai %d, meu filho é %d\nvariavel %d\n", 
            pai, filho, variavel);
    }
    return 0;
}
