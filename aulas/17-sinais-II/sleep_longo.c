#include <unistd.h>
#include <stdio.h>
#include <signal.h>


void handler(int num) {
    printf("Interrompi o sleep!\n");
    
}

int main(int argc, char *argv[]) {
    struct sigaction st;
    st.sa_handler = handler;
    st.sa_flags = SA_RESTART;
    sigemptyset(&st.sa_mask);
    sigaction(SIGTERM, &st, NULL);
    
    printf("Tempo restante: %d\n", sleep(20));

}
