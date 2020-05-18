#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int num, ret_eh_par, st;
    char nome_programa[] = "./eh_par";
    char arg1[20];
    char *args[3];

    do {
        scanf("%d", &num);
        if (fork() == 0) {
            sprintf(arg1, "%d", num);
            args[0] = nome_programa;
            args[1] = arg1;
            args[2] = NULL;
            execvp(nome_programa, args);
        } else {
            wait(&st);
            if (WIFEXITED(st)) {
                ret_eh_par = (char) WEXITSTATUS(st);
                if (ret_eh_par == 0) {
                    printf("Eh ímpar\n");
                } else if (ret_eh_par == 1) {
                    printf("Eh par\n");
                } 
            }
        }

    } while (ret_eh_par != -1);

    return 0;
}