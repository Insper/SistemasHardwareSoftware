
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *minha_thread(void *arg) {
    printf("Hello thread!\n");
    return NULL;
}


void *minha_thread2(void *arg) {
    printf("Hello thread2!\n");
    return NULL;
}


void *minha_thread3(void *arg) {
    printf("Hello thread3!\n");
    return NULL;
}


void *minha_thread4(void *arg) {
    printf("Hello thread4!\n");
    return NULL;
}


int main() {
    pthread_t tid[4]; 
    
    int error = pthread_create(&tid[0], 0, minha_thread, NULL);
    error = pthread_create(&tid[1], 0, minha_thread2, NULL);
    error = pthread_create(&tid[2], 0, minha_thread3, NULL);
    error = pthread_create(&tid[3], 0, minha_thread4, NULL);
    
    printf("Hello main\n");
    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
        
    return 0;
}
