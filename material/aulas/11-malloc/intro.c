#include <stdio.h>
#include <stdlib.h>

#define N 3000000

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
