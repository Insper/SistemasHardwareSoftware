#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int num_vezes = 0;
void sig_handler(int num) {
    printf("Chamou Ctrl+C: %d\n", num_vezes);
    if (num_vezes == 3) {
        struct sigaction s;
        s.sa_handler = SIG_DFL;
        sigemptyset(&s.sa_mask);
        printf("Chamou sigaction! %d\n", num_vezes);
        sigaction(SIGINT, &s, NULL);
    }
    num_vezes++;
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
