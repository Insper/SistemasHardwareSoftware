/*
compile:
gcc rdv.c -o rdv -pthread
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *thread1(void *arg) {
    printf("A\n");

    // TODO: implemente aqui o RDV

    printf("C\n");

    return NULL;
}

void *thread2(void *arg) {
    printf("B\n");

    // TODO: implemente aqui o RDV

    printf("D\n");

    return NULL;
}
int main() {
    // TODO: Crie TODAS as threads. Voce deve utilizar semaforos para sincronizacao.
    
    
    // TODO: Espere por TODAS as threads

    return 0;
}
