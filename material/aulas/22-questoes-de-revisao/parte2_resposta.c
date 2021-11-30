#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

struct rdv_args {
    sem_t *s1;
    sem_t *s2;
    sem_t *s3;
    sem_t *s4;
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

    printf("B\n");

    sem_post(arg->s2);
    sem_post(arg->s2);
    sem_post(arg->s2);

    sem_wait(arg->s1);
    sem_wait(arg->s3);
    sem_wait(arg->s4);
    
    printf("D\n");

    return NULL;
}

void *thread3(void *_arg) {
    struct rdv_args *arg = _arg;


    printf("E\n");

    sem_post(arg->s3);
    sem_post(arg->s3);

    sem_wait(arg->s2);
    sem_wait(arg->s4);
    
    printf("F\n");

    return NULL;
}

void *thread4(void *_arg) {
    struct rdv_args *arg = _arg;


    printf("G\n");

    sem_post(arg->s4);
    sem_post(arg->s4);
    
    sem_wait(arg->s2);
    sem_wait(arg->s3);
    
    printf("H\n");

    return NULL;
}

int main() {

    // Cria e configura semaforos
    sem_t s1, s2, s3, s4;
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);
    sem_init(&s4, 0, 0);

    // Configuracao da passagem de parametros
    struct rdv_args *args = malloc(sizeof(struct rdv_args));
    args->s1 = &s1;
    args->s2 = &s2;
    args->s3 = &s3;
    args->s4 = &s4;
    
    // cria threads
    pthread_t *tid = malloc(sizeof(pthread_t) * 4);
    pthread_create(&tid[0], NULL, thread1, args);
    pthread_create(&tid[1], NULL, thread2, args);
    pthread_create(&tid[2], NULL, thread3, args);
    pthread_create(&tid[3], NULL, thread4, args);

    // espera pelas threads
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);

    // liberar recursos alocados dinamicamente
    free(tid);
    free(args);

    // destroi semaforos
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    sem_destroy(&s4);

    return 0;
}
