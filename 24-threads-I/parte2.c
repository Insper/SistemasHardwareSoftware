#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *minha_thread(void *arg) {
    int *i = (int *) arg;
    printf("Hello thread! %d\n", *i);

    return NULL;
}


int main() {
    pthread_t *tids = malloc(4 * sizeof(pthread_t));
    int *vi = malloc(4 * sizeof(int));
    
    for (int i = 0; i < 4; i++) {
        vi[i] = i;
        pthread_create(&tids[i], NULL, minha_thread, &vi[i]);
    }
    
    
    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
    }
    
    return 0;
}

