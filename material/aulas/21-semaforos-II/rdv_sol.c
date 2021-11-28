// Este é um exercício da aula 20. A resolução pelo professor foi feita na aual 21.
// Deixei cópia tanto na aula 20 quanto 21.

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct rdv_args {
    sem_t *s1;
    sem_t *s2;
};

void *thread1(void *_arg) {
    struct rdv_args *arg = _arg;

    printf("A\n");

    sem_post(arg->s1);
    sem_wait(arg->s2);
    
    printf("C\n");

    return NULL;
}

void *thread2(void *_arg) {
    struct rdv_args *arg = _arg;

    sleep(5);
    printf("B\n");

    sem_post(arg->s2);
    sem_wait(arg->s1);
    
    printf("D\n");

    return NULL;
}

int main() {

    // Cria e configura semaforos
    sem_t s1, s2;
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);

    // Configuracao da passagem de parametros
    struct rdv_args *args = malloc(sizeof(struct rdv_args));
    args->s1 = &s1;
    args->s2 = &s2;
    
    // cria threads
    pthread_t *tid = malloc(sizeof(pthread_t) * 2);
    pthread_create(&tid[0], NULL, thread1, args);
    pthread_create(&tid[1], NULL, thread2, args);

    // espera pelas threads
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    // liberar recursos alocados dinamicamente
    free(tid);
    free(args);

    // destroi semaforos
    sem_destroy(&s1);
    sem_destroy(&s2);
    
    return 0;
}