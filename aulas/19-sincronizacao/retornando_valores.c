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
    int *retorno=malloc(sizeof(int));
    printf("Hello world![%d][%d]\n",par->x, par->y);
    *retorno = par->x+par->y;
    return retorno;
}
int main() {
    pthread_t id1;
    Targ a;
    int *retorno;
    a.x = 10;
    a.y = 20;

    pthread_create(&id1,NULL,(void*)f1,&a);
    
    // thread principal espera as threads filhas
    pthread_join(id1,(void**)&retorno);
    printf("retorno t1 [%d].\n",*retorno);
    free(retorno);

    printf("fim do programa.\n");
   
    return 0;
}