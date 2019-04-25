#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sorteio() {
    /* Aloca espaco para 25 milhoes de inteiros. Aprox 100MB em memoria */
    int *face = malloc(25000000 * sizeof(int));

    if (face == NULL ) {
        perror("Alocacao falhou!");
        exit(EXIT_FAILURE);
    }

    /* Simula e guarda 100 milhoes de sorteios de um dado de seis faces */
    for (int i = 0; i < 25000000; i++) {
        *(face + i) = rand() % 6;
    }

    return 0;
}

int main(int argc, char *argv[]) {

    int opcao;
    time_t t;

    srand((unsigned) time(&t));

    do {
        sorteio();
        printf("Chamou a funcao sorteio... Digite 0 para sair: ");
        scanf("%d", &opcao);
    } while (opcao != 0);

    return 0;
}
