#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
    long l;
    char str_arg[100];
    int ret_value, status;

    do {
        scanf("%ld", &l);
        sprintf(str_arg, "%ld", l);
        
        char *args[] = {"./eh_par", str_arg, NULL};
        
        if (fork() == 0) {
            execvp("./eh_par", args);
        }
        
        wait(&status);
        if (WIFEXITED(status)) {
            ret_value = ((char) WEXITSTATUS(status));
            if (ret_value >= 0) {
                printf("eh_par: %d\n", ret_value);
            }
        }
         
    } while (ret_value >= 0);
}
