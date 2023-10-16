#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t filho;

    filho = fork();

    if (filho == 0) {
        sleep(3);
        printf("Acabei filho %d\n", 1);        
        return 2;
    } else {
        int wstatus;

        wait(&wstatus);
        printf("Filho acabou\n");

        // Utiliza macro para ler um "pedaço" (um ou mais bits) de wstatus
        printf("Terminou normal?: %d\n", WIFEXITED(wstatus)); // lê 0 ou 1
        if (WIFEXITED(wstatus)) { // se terminou normalmente
            printf("Valor de retorno: %d\n", WEXITSTATUS(wstatus)); // lê o byte menos significativo do return do filho
        }
        
    }
    return 0;
}
