#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *minha_thread(void *arg) {
    int *i = (int *) arg;
    printf("Hello thread! %d\n", *i);

    return NULL;
}

pthread_t *criar_threads(int n, int **vec) {
    pthread_t *tids = malloc(sizeof(pthread_t) * n);

    int *v = *vec;

    for (int i = 0; i < n; i++) {
        v[i] = i;
        pthread_create(&tids[i], NULL, minha_thread, &v[i]);
    }

    return tids;
}

int main() {

    int *vec;

    vec = malloc(sizeof(int) * 4);


    pthread_t *tids = criar_threads(4, &vec);
    

    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
    }

    free(vec);

    return 0;
}
