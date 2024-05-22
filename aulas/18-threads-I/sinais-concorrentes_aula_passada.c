#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int status = 0;

void operacao_lenta() {
    sleep(10);
}


void sigint_handler(int num) {
    status += 1;
    printf("Chamou Ctrl+C; status=%d\n", status);
    operacao_lenta();
    printf("SIGINT: Vou usar status agora! status=%d\n", status);

}

void sigterm_handler(int num) {
    status += 1;
    printf("Recebi SIGTERM; status=%d\n", status);
    operacao_lenta();
    printf("SIGTERM: Vou usar status agora! status=%d\n", status);
}

int main() {
    /* TODO: registar SIGINT aqui. */
    struct sigaction handler_sigint;
    
    handler_sigint.sa_handler = sigint_handler;
    handler_sigint.sa_flags = 0;
    sigemptyset(&handler_sigint.sa_mask);
    // bloqueia o SIGTERM
    sigaddset(&handler_sigint.sa_mask, SIGTERM);

    sigaction(SIGINT, &handler_sigint, NULL);

    /* TODO: registar SIGTERM aqui. */

    struct sigaction handler_sigterm;

    handler_sigterm.sa_handler = sigterm_handler;
    handler_sigterm.sa_flags = 0;
    sigemptyset(&handler_sigterm.sa_mask);
    // bloqueia o SIGINT
    sigaddset(&handler_sigterm.sa_mask, SIGINT);

    sigaction(SIGTERM, &handler_sigterm, NULL);

    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
