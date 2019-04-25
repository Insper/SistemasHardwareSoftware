#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>

int main() {
    pid_t f1, f2;
    long var = 20;

    f1 = fork();

    if (f1 == 0) {
        var *= 2;
    }

    f2 = fork();
    if (f2 == 0) {
        var += 3;
        if (f1 == 0) {
            wait(NULL);
        }
    } else {
        var -= 3;
    }

    printf("Meu var: %ld  f1 %d f2 %d, meu pid: %d\n", var, f1, f2, getpid());


}
