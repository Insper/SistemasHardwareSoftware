#include <stdio.h>
#include <stddef.h>

struct rec {
    char a;
    int i[2];
    double next;
} ;

int main() {
    struct rec registro;

    printf("tamanho: registro.a %d\n", sizeof(registro.a));
    printf("tamanho: registro.i %d\n", sizeof(registro.i));
    printf("tamanho: registro.next %d\n", sizeof(registro.next));
    
    printf("offset: registro.a %d\n", offsetof(struct rec,a));
    printf("offset: registro.i %d\n", offsetof(struct rec,i));
    printf("offset: registro.next %d\n", offsetof(struct rec,next));

    printf("endereço: registro.a %p\n", &(registro.a));
    printf("endereço: registro.i %p\n", &(registro.i));
    printf("endereço: registro.next %p\n", &(registro.next));
    
    return 0;
}
