#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

struct semaforos{
    sem_t *s1;
    sem_t *s2;
};

void * thread1(void * arg){
    struct semaforos * sem_rdv = arg;
    //sleep(1);
    printf("A\n");
    sem_post(sem_rdv->s1);
    sem_wait(sem_rdv->s2);
    printf("C\n");
}

void * thread2(void * arg){
    struct semaforos * sem_rdv = arg;

    printf("B\n");
    sem_post(sem_rdv->s2);
    sem_wait(sem_rdv->s1);
    printf("D\n");
}

int main(){

    pthread_t id1, id2;
    sem_t s1, s2;
    struct semaforos sem_rdv;

    // 1o endereco do semaforo
    // 2o 0 inndica que o semaforo sera compartilhado com outras threads
    // 3o valor da thread
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    sem_rdv.s1 = &s1;
    sem_rdv.s2 = &s2;

    pthread_create(&id1, NULL, thread1, &sem_rdv);
    pthread_create(&id2, NULL, thread2, &sem_rdv);

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

}