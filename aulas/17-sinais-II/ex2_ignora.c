// gcc ex2_ignora.c -o ex2

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main() {
    struct sigaction sa;
    // Define a ação: ignorar o sinal
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    // Loop infinito para demonstrar
    while (1) {
        printf("Trabalhando...\n");
        printf("PID do processo: %d\n", getpid());
        printf("SIGINT (Ctrl+C) será ignorado.\n");
        sleep(1);
    }

    return 0;
}