// para compilar use:
// gcc rdv.c -o rdv -pthread
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Note que nao usamos variavel global e mutex
typedef struct {
    sem_t *s1, *s2;
} t_arg;

void *thread1(void *_arg) {
    t_arg *arg = _arg;

    printf("A\n");
    sem_post(arg->s1); // thread1 avisa que chegou na barreira
    sem_wait(arg->s2); // Pergunta se a outra thread chegou na barreira
    printf("C\n");

    return NULL;
}

void *thread2(void *_arg) {
    t_arg *arg = _arg;

    printf("B\n");
    sem_post(arg->s2); // thread2 avisa que chegou na barreira
    sem_wait(arg->s1); // Pergunta se a outra thread chegou na barreira
    printf("D\n");

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t *tid = malloc(sizeof(pthread_t) * 2);

    t_arg *arg = malloc(sizeof(t_arg));

    sem_t *s1 = malloc(sizeof(sem_t));
    sem_t *s2 = malloc(sizeof(sem_t));

    sem_init(s1, 0, 0);
    sem_init(s2, 0, 0);

    arg->s1 = s1;
    arg->s2 = s2;

    pthread_create(&tid[0], NULL, thread1, arg);

    pthread_create(&tid[1], NULL, thread2, arg);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    sem_destroy(s1);
    sem_destroy(s2);

    free(tid);
    free(s1);
    free(s2);
    free(arg);

    return 0;
}