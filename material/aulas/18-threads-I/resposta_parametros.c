#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *tarefa_print_i(void *arg) {
    int *i = (int *) arg;
    printf("Estou na Thread %d\n", *i);
    return NULL;
}

int main() {
    pthread_t tid[4];

    int *vec = malloc(sizeof(int) * 4);

    for (int i=0; i<4; i++) {
        vec[i] = i;
        pthread_create(&tid[i], NULL, tarefa_print_i, &vec[i]);
        pthread_join(tid[i], NULL); //PQ NAO EH UMA BOA: cada nova thread será criada apenas apos a anterior terminar.
    }

    return 0;
}