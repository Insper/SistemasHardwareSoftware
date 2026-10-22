#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct{
    int x;
    int y;
    int ret;
}Targ;
//int a; // variavel global
void * f1(void *arg) {
    Targ *par = (Targ*) arg;
    printf("Hello world![%d][%d]\n",par->x, par->y);
    par->ret = par->x+par->y;
    return NULL;
}
int main() {
    pthread_t id1;
    Targ a;
    a.x = 10;
    a.y = 20;

    pthread_create(&id1,NULL,(void*)f1,&a);
    
    // thread principal espera as threads filhas
    pthread_join(id1,NULL);
    printf("retorno t1 [%d].\n",a.ret);

    printf("fim do programa.\n");
   
    return 0;
}