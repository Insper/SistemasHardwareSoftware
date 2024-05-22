// gcc -g barrier_sol.c -o barrier_sol -pthread
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 4

struct barreira_args{
    int num_barrier;
    pthread_mutex_t *mutex;
    sem_t  *sem_barrier;

};
void *thread_barreira(void *arg) {
    struct barreira_args *barreira = arg;
    // NÃO altere este print, ele simula uma tarefa
    printf("Antes da barreira\n");

    // TODO: implemente a barreira aqui
    pthread_mutex_lock(barreira->mutex);
    barreira->num_barrier++;
    pthread_mutex_unlock(barreira->mutex);

    if( barreira->num_barrier == 4){
        // libera as outras 3 threads
        for(int i=0;i<N-1;i++)
            sem_post(barreira->sem_barrier);

    }
    else
        sem_wait(barreira->sem_barrier);

    // NÃO altere este print, ele simula uma tarefa
    printf("Depois da barreira\n");

    return NULL;
}

int main() {
    struct barreira_args parametro;
    pthread_t id_thread[N];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    sem_t sem_barrier; // para bloquear as outras threads

    // Configura semáforo
    //sem_init(sem_t *sem, int pshared, unsigned int value);
    // 1o endereco do semaforo
    // 2o 0 inndica que o semaforo sera compartilhado com outras threads
    // 3o valor da thread
    sem_init(&sem_barrier, 0, 0);

    // TODO: crie 4 threads rodando o código acima
    parametro.num_barrier = 0;
    parametro.mutex = &mutex;
    parametro.sem_barrier = &sem_barrier;
    

    for(int i=0; i < N; i++){
        pthread_create(&id_thread[i],NULL, thread_barreira, &parametro);
    }
    
    // TODO: espere por elas
    for(int i=0; i < N; i++){
        pthread_join(id_thread[i],NULL);
    }
    return 0;
}
