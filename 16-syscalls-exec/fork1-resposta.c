#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/wait.h>

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

    f1 = fork(); 
    if (f1 == 0) {
        func1();
    }
    
    f2 = fork();
    if (f2 == 0) {
        func2();
    }
    
    f3 = fork();
    if (f3 == 0) {
        func3();
    }
    
    
    for (int i = 0; i < 3; i++) {
        int status;
        pid_t fim = wait(&status);
        
        if (fim == f1) {
            printf("func1 acabou!\n");
        } else if (fim == f2) {
            printf("func2 acabou!\n");
        } else if (fim == f3) {
            printf("func3 acabou!\n");
        } 
        
        if (WIFEXITED(status)) {
            printf("O processo acabou normalmente e retornou %d\n", WEXITSTATUS(status));
        } else {
            printf("O processo filho deu erro!\n");
        }
        
    }
    
    // faça forks para executar func1, func2 e func3 em um processo filho
    
    // espere por cada um dos 3 e diga seu valor de retorno e se terminou
    // corretamente ou se deu pau. 

    return 0;
}
