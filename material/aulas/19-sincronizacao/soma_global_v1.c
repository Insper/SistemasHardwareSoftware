#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
};

double soma = 0;
void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        soma = soma + spa->vetor[i];
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }


    /* TODO: criar thread_t e soma_parcial_args aqui */
    pthread_t *tid = malloc(sizeof(pthread_t) * 4);

    struct soma_parcial_args *vargt = malloc(sizeof(struct soma_parcial_args) * 4);

    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        vargt[i].vetor = vetor;
        vargt[i].start = i * n / 4;
        if (i < 3) {
            vargt[i].end = (i + 1) * n / 4;
        } else {
            vargt[i].end = n;
        }

        pthread_create(&tid[i], NULL, soma_parcial, &vargt[i]);
    }

    /* TODO: esperar pela conclusão*/
    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }


    printf("Paralela: %lf\n", soma);

    soma = 0;
    struct soma_parcial_args aa;
    aa.vetor = vetor;
    aa.start = 0;
    aa.end = n;
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", soma);

    free(vetor);
    free(tid);
    free(vargt);

    return 0;
}
