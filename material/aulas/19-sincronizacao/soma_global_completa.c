// gcc soma_global_completa.c -o soma_global_completa -pthread

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    pthread_mutex_t *mutex_soma;
    int start, end;
};

double soma = 0;
void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;
    double soma_local=0;
    for (int i = spa->start; i < spa->end; i++) {
        /*
        pthread_mutex_lock(spa->mutex_soma);
        soma += spa->vetor[i];
        pthread_mutex_unlock(spa->mutex_soma);
        */
       soma_local += spa->vetor[i];
    }
    pthread_mutex_lock(spa->mutex_soma);
    soma += soma_local;
    pthread_mutex_unlock(spa->mutex_soma);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p_id[4];
    struct soma_parcial_args vet_soma_parcial[4];
    double *vetor = NULL;
    int n;
    pthread_mutex_t mutex_soma = PTHREAD_MUTEX_INITIALIZER;

    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }


    /* TODO: criar thread_t e soma_parcial_args aqui */
    int regiao = n/4;
    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        vet_soma_parcial[i].vetor = vetor;
        vet_soma_parcial[i].mutex_soma = &mutex_soma;
        vet_soma_parcial[i].start = i*regiao;
        if( i==3)
            vet_soma_parcial[i].end = n;
        else
            vet_soma_parcial[i].end = (i+1)*regiao;
        pthread_create(&p_id[i],NULL,soma_parcial,&vet_soma_parcial[i]);    
    }

    /* TODO: esperar pela conclusão*/
    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        pthread_join(p_id[i],NULL);    
    }
    printf("Paralela: %lf\n", soma);

    soma = 0;
    struct soma_parcial_args aa;
    aa.vetor = vetor;
    aa.mutex_soma = &mutex_soma;
    aa.start = 0;
    aa.end = n;
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", soma);

    return 0;
}
