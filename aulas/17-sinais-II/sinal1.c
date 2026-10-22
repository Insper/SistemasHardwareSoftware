#include <stdio.h>
#include <unistd.h>

// Fora da main, criamos a função que será nosso handler
void sig_handler(int num) {
    // faz algo aqui
}

int main() {
    /* Dentro da main, uma das primeiras coisas que fazemos é
    registrar nosso handler */


    printf("Meu pid: %d\n", getpid());
    
    while(1) {
        sleep(1);
    }
    return 0;
}
