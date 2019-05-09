#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int flag = 0;

void sig_handler(int num) {
    printf("Chamou Ctrl+C\n");
    flag = 1;
}

int main() {
    int count = 0;
    struct sigaction s;
    s.sa_handler = sig_handler;
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);

    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
        if (flag) {
            count++;
            flag = 0;
        }
    }
    return 0;
}
