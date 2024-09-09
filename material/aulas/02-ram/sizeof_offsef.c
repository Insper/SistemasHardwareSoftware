#include <stdio.h>
#include <stddef.h>

struct rec {
    char a;
    double v;
    int i[2];
} ;

int main() {
    struct rec registro;

    printf("tamanho: registro.a %d\n", sizeof(registro.a));
    printf("tamanho: registro.v %d\n", sizeof(registro.v));
    printf("tamanho: registro.i %d\n", sizeof(registro.i));
    printf("tamanho: registro %d\n", sizeof(registro));
    
    printf("offset: registro.a %d\n", offsetof(struct rec,a));
    printf("offset: registro.v %d\n", offsetof(struct rec,v));
    printf("offset: registro.i %d\n", offsetof(struct rec,i));
    

    printf("endereço: registro.a %p\n", &(registro.a));
    printf("endereço: registro.v %p\n", &(registro.v));
    printf("endereço: registro.i %p\n", &(registro.i));

    
    return 0;
}
