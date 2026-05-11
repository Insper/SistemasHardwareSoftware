#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
    pthread_mutex_t *s;
};

double soma = 0;
void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;
    double soma_local=0;
    for (int i = spa->start; i < spa->end; i++) {
        soma_local+=spa->vetor[i]; // T2
    }
    pthread_mutex_lock(spa->s); // T3,T4, T1
    soma += soma_local; 
    pthread_mutex_unlock(spa->s);

    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }

    /* TODO: criar pthread_t e soma_parcial_args aqui */
    pthread_t id[4];
    struct soma_parcial_args args_vet[4];
    
    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        int regiao = n/4;
        args_vet[i].start = i*regiao;
        args_vet[i].end = (i+1)*regiao;
        if( i == 3 )
            args_vet[i].end = n;

        args_vet[i].vetor = vetor;
        args_vet[i].s = &mutex;
        pthread_create(&id[i],NULL,soma_parcial,&args_vet[i]);
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
    aa.s = &mutex;
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", soma);

    return 0;
}
