#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int rodando = 1;
    pid_t filho;

    filho = fork();

    if (filho == 0) {
        printf("Acabei filho\n");
        rodando = 0;
    } else {
        while (rodando) {
            printf("Esperando o filho acabar!\n");
            sleep(1);
        }
    }
    return 0;
}
