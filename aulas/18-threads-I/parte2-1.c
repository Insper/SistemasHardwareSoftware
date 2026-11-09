#include <pthread.h>
#include <stdio.h>

void *minha_thread(void *arg) {
    int *i = (int *) arg;
    printf("Hello thread! %d\n", *i);

    return NULL;
}


int main() {
    pthread_t tid[4];
    
    for (int i = 0; i < 4; i++) {
        pthread_create(&tid[i], NULL, minha_thread, &i);
    }
    
    
    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }
    
    return 0;
}
