#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int num) {
    static int counter = 0;
    printf("Chamou Ctrl+C\n");
    counter++;
    if (counter > 3) {
        exit(0);
    }
}

int main() {
    printf("Meu pid: %d\n", getpid());
    struct sigaction s;
    s.sa_handler = sig_handler; // aqui vai a função a ser executada
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;

    sigaction(SIGINT, &s, NULL);

    while(1) {
        sleep(1);
    }
    return 0;
}
