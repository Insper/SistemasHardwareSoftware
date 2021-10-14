#include <stdio.h>
#include <stdlib.h>

#define N 13

int main(int argc, char *argv[]) {
    int *vetor = malloc(N * sizeof(int));
    if (vetor == NULL) {
        exit(-1);
    }
    int i;

    for (i = 0; i < N; i++) { // problema corrigido!
        vetor[i] = i;
    }

    for (i = 0; i < N; i++) { // problema corrigido!
        printf("Elemento %d: %d\n", i+1, vetor[i]);
    }

    free(vetor); //memória liberada

    return 0;
}
