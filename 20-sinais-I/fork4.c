#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void func1() {
    while (1) {
        printf("loop infinito! meu pid: %d\n", getpid());
        sleep(2);
    }
}


int main() {
    pid_t f1, f2, f3;

    printf("pai: pid %d ppid %d\n", getpid(), getppid());

    f1 = fork();
    if (f1 == 0) {
        func1();
        exit(0);
    } 

    sleep(10);

    // verifica se o processo filho acabou
    // termine se ele nao tiver finalizado!
    
    return 0;
}