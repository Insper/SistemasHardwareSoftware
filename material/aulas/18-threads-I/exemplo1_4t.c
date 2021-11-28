
#include <pthread.h>
#include <stdio.h>

void *minha_thread1(void *arg) {
    printf("Hello thread 1!\n");
    return NULL;
}

void *minha_thread2(void *arg) {
    printf("Hello thread 2!\n");
    return NULL;
}


void *minha_thread3(void *arg) {
    printf("Hello thread 3!\n");
    return NULL;
}


void *minha_thread4(void *arg) {
    printf("Tchau! thread!\n");
    return NULL;
}



int main() {
    pthread_t tid1, tid2, tid3, tid4;
    
    int error = pthread_create(&tid1, NULL, minha_thread1, NULL);
    error = pthread_create(&tid2, NULL, minha_thread2, NULL);
    error = pthread_create(&tid3, NULL, minha_thread3, NULL);
    error = pthread_create(&tid4, NULL, minha_thread4, NULL);

    printf("Hello main\n");
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    
    return 0;
}
