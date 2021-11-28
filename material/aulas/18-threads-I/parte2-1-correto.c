#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *minha_thread(void *arg) {
    int *i = (int *) arg;
    printf("Hello thread! %d\n", *i);

    return NULL;
}


int main() {
    pthread_t tid[4];

    int *vec = malloc(sizeof(int) * 4);
    
    for (int i = 0; i < 4; i++) {
        vec[i] = i;
        pthread_create(&tid[i], NULL, minha_thread, &vec[i]);
    }
    
    
    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }

    free(vec);
    
    return 0;
}
