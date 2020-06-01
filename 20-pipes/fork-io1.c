#include <stdio.h>

void funcao_lenta() {
    for (int i = 0; i < 5; i++) {
        printf("Filho %d", i);
        sleep(2);
        printf(" -- Fim Filho %d\n", i);
    }
}

void funcao_lenta_pai() {
    for (int i = 0; i < 10; i++) {
        printf("Pai %d", i);
        sleep(1);
        printf(" -- Fim Pai %d\n", i);
    }
}

int main(int argc, char *argv[]) {
    /* TODO: preencher o main com os exercícios.
             as funções acima não devem ser modificadas */

    return 0;
}
