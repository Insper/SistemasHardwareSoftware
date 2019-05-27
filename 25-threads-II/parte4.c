#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
    double soma;
};

void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;

    double soma = 0;
    for (int i = spa->start; i < spa->end; i++) {
        soma += spa->vetor[i];
    }
    spa->soma = soma;

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
    spa1.soma = 0;

    spa2.vetor = vetor;
    spa2.start = n/2;
    spa2.end = n;
    spa2.soma = 0;

    pthread_create(&t1, NULL, soma_parcial, &spa1);
    pthread_create(&t2, NULL, soma_parcial, &spa2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    double soma = spa1.soma + spa2.soma;
    printf("%lf\n", soma);

    return 0;
}
