#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N_THREADS 10
#define MAX_EXEC 4

typedef struct {
    sem_t *semaph;
} limite_args_t;

void *faz_algo(void *_arg) {
    limite_args_t *arg = _arg;

    sem_wait(arg->semaph); // semelhante a uma reserva de recurso

    printf("Thread Iniciando!\n");
    sleep(random() % 10);
    printf("Thread Finalizando!\n");

    sem_post(arg->semaph); // semelhante a uma liberação de recurso

    return NULL;
}


int main() {

    // Cria e configura semaforos
    sem_t sem;
    sem_init(&sem, 0, MAX_EXEC);

    // Configuracao da passagem de parametros
    limite_args_t *arg = malloc(sizeof(limite_args_t));
    arg->semaph = &sem;
    
    // cria threads
    pthread_t *tid = malloc(sizeof(pthread_t) * N_THREADS);
    for (int i=0; i<N_THREADS; i++){
        pthread_create(&tid[i], NULL, faz_algo, arg);
    }
    

    // espera pelas threads
    for (int i=0; i<N_THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    // liberar recursos alocados dinamicamente
    free(tid);
    free(arg);

    // destroi semaforos
    sem_destroy(&sem);

    
    return 0;
}