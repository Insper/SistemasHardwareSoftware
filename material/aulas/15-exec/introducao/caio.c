#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    pid_t andre = fork();

    if (andre == 0) {
        printf("Faz algo no processo andre");
    } else {
        printf("Faz algo no pai (geralmente um wait)\n!");
    }

    return 0;
}

/*
char *args[] = {"./dom", NULL};
execvp(args[0], args);
*/