#include <stdio.h>
#include <stdlib.h>

#define N 12

int *aloca_vetor(int n) {
    int *vetor = malloc(n * sizeof(int));
    return vetor;
}

void atribui(int *vetor, int n) {
    for (int i = 0; i <= n; i++) { // problema!
        vetor[i] = i;
    }
}

int main(int argc, char *argv[]) {
    int *vetor = aloca_vetor(N);
    int i;

    atribui(vetor, N);

    for (i = 0; i <= N; i++) { // problema!
        printf("Elemento %d: %d\n", i+1, vetor[i]);
    }


    return 0;
}
