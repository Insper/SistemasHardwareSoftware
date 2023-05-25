#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct{
    int x;
    int y;
}Targ;
//int a; // variavel global
void * f1(void *arg) {
    Targ *par = (Targ*) arg;
    int *retorno=malloc(sizeof(Targ));
    //sleep(10);
    printf("Hello world![%d][%d]\n",par->x, par->y);
    *retorno = par->x+par->y;
    return retorno;
}
int main() {
    pthread_t id1, id2;
    Targ *a= malloc(sizeof(Targ));
    int *retorno=malloc(sizeof(int));;
    a->x = 10;
    a->y = 20;
    //f1();
    pthread_create(&id1,NULL,(void*)f1,a);
    
    pthread_create(&id2,NULL,(void*)f1,a);


    // thread principal espera as threads filhas
    pthread_join(id1,(void**)&retorno);
    printf("retonrno t1 [%d].\n",*retorno);

    pthread_join(id2,NULL);
    printf("fim do programa.\n");

    
    return 0;
}