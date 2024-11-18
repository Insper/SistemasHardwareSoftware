/*
compile:
gcc rdv.c -o rdv -pthread
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

struct semaforos{
    sem_t *sem1, *sem2;
};

void *thread1(void *arg) {
    struct semaforos *sem_rdv = arg;
    printf("A\n");

    // TODO: implemente aqui o RDV
    sem_post(sem_rdv->sem1);
    sem_wait(sem_rdv->sem2);
    printf("C\n");

    return NULL;
}

void *thread2(void *arg) {
    struct semaforos *sem_rdv = arg;
    printf("B\n");

    // TODO: implemente aqui o RDV
    sem_post(sem_rdv->sem2);
    sem_wait(sem_rdv->sem1);
    printf("D\n");

    return NULL;
}
int main() {
    
    pthread_t id1, id2;
    struct semaforos sem_rdv;
    // criar os semaforos
    sem_t sem1,sem2;
    // 1o - parametro: endereco do semaforo
    // 2o - parametro: int pshared, 0 compartilhado entre threads (mesmo processo) 1: compartilhado entre semaforos diferentes.
    // 3o - parametro: valor do semaforo
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    // preparando o argumento para o semaforo
    sem_rdv.sem1 = &sem1;
    sem_rdv.sem2 = &sem2;
    // TODO: Crie TODAS as threads. Voce deve utilizar semaforos para sincronizacao.
    pthread_create(&id1,NULL,thread1,&sem_rdv);
    pthread_create(&id2,NULL,thread2,&sem_rdv);
    // TODO: Espere por TODAS as threads
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    return 0;
}
