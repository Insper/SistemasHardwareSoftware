#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
};

double soma = 0;

pthread_mutex_t soma_mutex;

void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    for (int i = spa->start; i < spa->end; i++) {
        pthread_mutex_lock(&soma_mutex);
        soma += spa->vetor[i];
        pthread_mutex_unlock(&soma_mutex);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;

    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }

    pthread_t t1, t2;
    struct soma_parcial_args spa1, spa2;

    spa1.vetor = vetor;
    spa1.start = 0;
    spa1.end = n/2;

    spa2.vetor = vetor;
    spa2.start = n/2;
    spa2.end = n;

    pthread_mutex_init(&soma_mutex, NULL);

    pthread_create(&t1, NULL, soma_parcial, &spa1);
    pthread_create(&t2, NULL, soma_parcial, &spa2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("%lf\n", soma);

    return 0;
}
