#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int status = 0;

void sigint_handler(int num) {
    status += 1;
    printf("Chamou Ctrl+C; status=%d\n", status);
    sleep(10);
    printf("SIGINT: Vou usar status agora! status=%d\n", status);
}

void sigterm_handler(int num) {
    status += 1;
    printf("Recebi SIGTERM; status=%d\n", status);
    sleep(10);
    printf("SIGTERM: Vou usar status agora! status=%d\n", status);
}

int main() {
    struct sigaction sint;
    sint.sa_handler = sigint_handler;
    sigemptyset(&sint.sa_mask);
    sint.sa_flags = 0;
    sigaction(SIGINT, &sint, NULL);

    struct sigaction sterm;
    sterm.sa_handler = sigterm_handler;
    sigemptyset(&sterm.sa_mask);
    sterm.sa_flags = 0;
    sigaction(SIGTERM, &sterm, NULL);

    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
