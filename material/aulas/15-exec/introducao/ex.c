#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    pid_t filho = fork();

    if (filho == 0) {
        char prog[] = "./processa";
        // a lista de argumentos sempre começa com o nome do
        // programa e termina com NULL
        char *args[] = {"./processa", "quero ferias por favor nao sou idiota blz", NULL};

        execvp(prog, args);

        printf("Fim do exec!\n");
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
