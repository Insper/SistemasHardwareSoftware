#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>


int main() {
    pid_t filho;

    filho = fork();

    if (filho == 0) {
        sleep(5);
        printf("Acabei filho\n");
        return -1;
    } else {
        int wt;
        wait(&wt);
        if (WIFEXITED(wt)) {
            printf("Filhou acabou: %d\n",(char) WEXITSTATUS(wt));
        }

    }
    return 0;
}
