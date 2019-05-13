#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int num) {
    printf("Chamou Ctrl+C\n");
}

int main() {
    struct sigaction s;
    s.sa_handler = sig_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);

    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
