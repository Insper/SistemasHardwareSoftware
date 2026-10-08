#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile int count  = 0;
void sig_handler(int num) {
    printf("Chamou Ctrl+C\n");
    count++;
}

int main() {
    struct sigaction s;
    s.sa_handler = sig_handler; 
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
    
    if(count >= 3 ) return 0;

    printf("Meu pid: %d\n", getpid());
    
    while(1){
        sleep(1);
    }
    return 0;
}
