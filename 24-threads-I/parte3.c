#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

struct args {
    int i, j, res;
};

void *minha_thread(void *_arg) {
    struct args *args = (struct args*) _arg;
    printf("Hello thread! %d %d\n", args->i, args->j);
    args->res = args->i * args->j;
}


int main() {
    pthread_t *tids = malloc(4 * sizeof(pthread_t));
    struct args *argvec = malloc(4 * sizeof(struct args));
    
    for (int i = 0; i < 4; i++) {
        argvec[i].i = i;
        argvec[i].j = i + 1;
        pthread_create(&tids[i], NULL, minha_thread, &argvec[i]);
    }
    
    
    for (int i = 0; i < 4; i++) {
        pthread_join(tids[i], NULL);
        printf("Res %d: %d * %d = %d\n", i, argvec[i].i, argvec[i].j, argvec[i].res);
    }
    
    return 0;
}

