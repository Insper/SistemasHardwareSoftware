#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
};
// varivel global
double soma = 0;

void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        soma += spa->vetor[i];
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    struct soma_parcial_args *vet_aa;
    pthread_t *id;
    double *vetor = NULL;
    int n;
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }
    /* TODO: criar thread_t e soma_parcial_args aqui */
    soma = 0;
    vet_aa = malloc(4*sizeof(struct soma_parcial_args));
    id = malloc(4*sizeof(pthread_t));
    int regiao = n / 4;
    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        vet_aa[i].vetor = vetor;
        vet_aa[i].start = i*regiao;
        if( i==3)// ultima thread
            vet_aa[i].end = n;
        else   
            vet_aa[i].end = (i+1)*regiao;
        pthread_create(&id[i],NULL,soma_parcial,&vet_aa[i]);
    }

    /* TODO: esperar pela conclusão*/
    for (int i = 0; i < 4; i++) {
        pthread_join(id[i],NULL);
    }
    printf("Paralela: %lf\n", soma);

    soma = 0;
    struct soma_parcial_args aa;
    aa.vetor = vetor;
    aa.start = 0;
    aa.end = n;
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", soma);

    return 0;
}
