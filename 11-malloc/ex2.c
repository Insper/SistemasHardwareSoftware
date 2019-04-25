#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int *vetor = malloc(10 * sizeof(int));
    int i;

    for (i = 0; i <= 10; i++) {
        vetor[i] = i;
    }

    for (i = 0; i <= 10; i++) {
        printf("Elemento %d: %d\n", i+1, vetor[i]);
    }

    return 0;
}
