#include <stdio.h>

typedef struct {
    int id;
} thread_barrier_args;

void *thread_n(void *v) {
    thread_barrier_args *args = (thread_barrier_args *) v;

    printf("Parte 1 thread %d\n", args->id);

    // TODO: a barreira vai aqui

    printf("Pós barreira thread %d\n", args->id);

    return NULL;
}

int main() {
    int N = 10;

    // TODO: inicializar todas variáveis da barreira

    // TODO: criar e esperar N threads

    return 0;
}
