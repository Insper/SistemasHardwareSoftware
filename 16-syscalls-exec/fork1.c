#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void func1() {
    printf("Retornei 10\n");
    exit(10);
}

void func2() {
    while (1) {
        printf("loop infinito! meu pid: %d meu ppid: %d\n", getpid(), getppid());
        sleep(10);
    }
}

void func3() {
    printf("Fiz divisão por 0\n");
    int a = 1/0;
    exit(0);
}


int main() {
    pid_t f1, f2, f3;

    printf("pai: pid %d ppid %d\n", getpid(), getppid());

    // faça forks para executar func1, func2 e func3 em um processo filho
    
    // espere por cada um dos 3 e diga seu valor de retorno e se terminou
    // corretamente ou se deu pau. 

    return 0;
}
