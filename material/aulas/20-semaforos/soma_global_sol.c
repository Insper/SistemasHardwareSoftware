#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    pthread_mutex_t *mutex_thread;
    int start, end;
};

double soma = 0;
void *soma_parcial(void *_arg) {
    
    struct soma_parcial_args *spa = _arg;
    double soma_local = 0;

    for (int i = spa->start; i < spa->end; i++) {
        soma_local += spa->vetor[i];
    }
    pthread_mutex_lock(spa->mutex_thread);
    soma +=soma_local;
    pthread_mutex_unlock(spa->mutex_thread);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;
    pthread_t id_thread[4];

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    struct soma_parcial_args aa_trheads[4];
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }


    /* TODO: criar thread_t e soma_parcial_args aqui */
    int segmento = n / 4;
    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        aa_trheads[i].vetor = vetor;
        aa_trheads[i].mutex_thread = &mutex;
        aa_trheads[i].start = i*segmento;
        if( i < 3)
            aa_trheads[i].end = (i+1)*segmento;
        else
            aa_trheads[i].end = n;

        pthread_create(&id_thread[i],NULL,soma_parcial,&aa_trheads[i]);
    }
    /* TODO: esperar pela conclusão*/
    for (int i = 0; i < 4; i++){
        pthread_join(id_thread[i],NULL);
    }
    printf("Paralela: %lf\n", soma);

    soma = 0;
    struct soma_parcial_args aa;
    aa.vetor = vetor;
    aa.mutex_thread = &mutex;
    aa.start = 0;
    aa.end = n;
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", soma);

    return 0;
}
