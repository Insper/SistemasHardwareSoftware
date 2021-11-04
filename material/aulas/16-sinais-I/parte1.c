#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        int i = 1/0;
        printf("Divisão por zero!\n");
    }

    return 0;
}