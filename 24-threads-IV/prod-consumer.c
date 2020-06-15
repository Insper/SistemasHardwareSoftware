#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int num;
} prod_result;

prod_result *producer() {
    prod_result *pr = malloc(sizeof(*pr));
    pr->num = rand() % 10;

    struct timespec tm;
    tm.tv_sec = 0;
    tm.tv_nsec = pr->num * 100000000;
    nanosleep(&tm, NULL);

    return pr;
}


int consumer(prod_result *pr) {
    struct timespec tm;
    tm.tv_sec = 0;
    tm.tv_nsec = pr->num * 300000000;
    nanosleep(&tm, NULL);

    return pr->num * 2;
}

int main() {
    int N = 50;

    for (int i = 0; i < N; i++) {
        prod_result *pr = producer();
        int res = consumer(pr);
        printf("Step: %d, pr->num %d, res %d\n", i, pr->num, res);
        free(pr);

    }

    return 0;
}

/* TODO: Responda as perguntas abaixo após finalizar sua implementação.


1. Quanto tempo demora a versão original do código?

2. Quanto tempo demora a versão Produtor-Consumidor 1-1? Seu programa deverá ter ganho de desempenho considerável.

3. Como estes tempos se relacionam com os tamanhos dos nanosleep usados nas funções. Você pode assumir que rand() sempre retorna 1.

4. Explique como você fez a sincronização entre as threads. Para cada semáforo explique seu propósito e valor inicial. Para cada mutex aponte qual recurso compartilhado ele protege.

*/
