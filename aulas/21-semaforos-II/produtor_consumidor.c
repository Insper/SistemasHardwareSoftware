// para compilar use
// gcc produtor_consumidor.c -o produtor_consumidor -pthread
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 4

struct pd_args
{
    int tarefas[N];
    pthread_mutex_t *mutex;
    sem_t *cheio;
    sem_t *vazio;
};

int produzir(int i){
    int item = rand()%100;
    return item;

}
void *produtor(void *_arg) {
    struct pd_args *args = _arg;
    int i=0;

    while( 1 ){
        int item = produzir(i);
        sem_wait(args->vazio);
        //inserir(item)
        pthread_mutex_lock(args->mutex);
        args->tarefas[i] = item;
        pthread_mutex_unlock(args->mutex);
        i=(i+1)%N;

        sem_post(args->cheio);

    }
    return NULL;
}

void consumir(int item){
    // simula lentidao
    sleep(1);
     
    printf("consumido: %d\n",item);
    fflush(stdout);
}
void *consumidor(void *_arg) {
    struct pd_args *args = _arg;
    int i=0;
    while( 1 ){
        sem_wait(args->cheio);
        
        pthread_mutex_lock(args->mutex);
        // item = retirar();
        int item = args->tarefas[i];
        pthread_mutex_unlock(args->mutex);
        i=(i+1)%N;

        sem_post(args->vazio);
        consumir(item);

    }
    
    

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t id1, id2;
    sem_t cheio, vazio;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    struct pd_args pd_parametros;

    // 1o endereco do semaforo
    // 2o 0 inndica que o semaforo sera compartilhado com outras threads
    // 3o valor da thread
    sem_init(&cheio, 0, 0);
    sem_init(&vazio, 0, N);
    pd_parametros.mutex = &mutex;
    pd_parametros.cheio = &cheio;
    pd_parametros.vazio = &vazio;

    srand(123); // inicia o gerador de numero aleatorio
    printf("Produtor/Consumidor.\n");
    pthread_create(&id1, NULL, consumidor, &pd_parametros);
    pthread_create(&id2, NULL, produtor, &pd_parametros);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    
    return 0;
}