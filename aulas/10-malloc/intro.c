#include <stdio.h>
#include <stdlib.h>

// Tente aumentar este valor, o que acontece quando testa 2 milhões, 3 milhões?
#define N 100

int *cria_vec() {
    int vec[100];
    return vec;
}

void atribui(int *vetor, int n) {
    for (int i = 0; i < n; i++) {
        vetor[i] = i;
    }
}

int main(int argc, char *argv[]) {
    int vetor[N];

    printf("Preenchendo o array...\n");
    atribui(vetor, N);

    printf("Finalizado! Pressione alguma tecla para sair...");
    getchar();
    
    return 0;
}
