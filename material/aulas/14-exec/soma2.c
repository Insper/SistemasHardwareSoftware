#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    if (argc < 3) {
        printf("Erro!\n");
        return -1;
    }
    double soma = 0.0;
    for (int i=1; i<argc; i++) {
        soma += atof(argv[i]);
    }

    printf("Soma: %lf\n", soma);

    return 0;
}
