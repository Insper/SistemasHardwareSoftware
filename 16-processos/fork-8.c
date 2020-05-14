#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t f;
    int i = 0;
    printf("Pai: %d, id %d\n", getpid(), i);

    for (i = 1; i <= 8; i++) {
        f = fork();
        if (f == 0) {
            printf("Filho %d Pai: %d id %d\n", getpid(), getppid(), i);   
            break;
        }
    }

    if (f == 0) {
        return i;
    }

    int w;
    pid_t f2 = wait(&w);
    printf("id do primeiro filho a acabar: %d, pid %d\n", WEXITSTATUS(w), f2);
    return 0;
    
}
