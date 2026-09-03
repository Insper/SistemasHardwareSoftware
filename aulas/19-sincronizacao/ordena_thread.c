// Para compilar use:
// gcc -g ordena_thread.c -o ordena_thread -pthread
// Para testar se há vazamento de memória use:
// valgrind --leak-check=yes ./ordena_thread 4 3 4 5 1 

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *ordena_thread(void *arg) {
    char *valor_str = (char *)arg;
    int valor = atoi(valor_str);
    sleep(valor);
    printf("%d ",valor);
    return NULL;
}
int main(int argc, char *argv[]) {
    argc--; // reduz o numero de argumentos, pois os numeros vem depois do nome do executável
    pthread_t *tid = malloc(sizeof(pthread_t)*argc);
    
    printf("Numeros ordenados: ");
    for(int i=0;i<argc;i++)
        pthread_create(&tid[i], NULL, ordena_thread, argv[i+1]);

    for(int i=0;i<argc;i++)
        pthread_join(tid[i], NULL);
    
    printf("\n");
    free(tid);
    return 0;
}
