#include <stdio.h>
#include <unistd.h>

void sig_handler(int num) {
    printf("Chamou Ctrl+C\n");
}

int main() {
    /* TODO: registre a função sig_handler
     * como handler do sinal SIGINT
     */
    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
