#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void func1() {
    printf("Acabei rapidinho!\n");
}

int main() {
    pid_t f1, f2, f3;

    printf("pai: pid %d ppid %d\n", getpid(), getppid());

    f1 = fork();
    if (f1 == 0) {
        func1();
        exit(0);
    } 
    
    while (1) {
        ;
    }
    
    return 0;
}