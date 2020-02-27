#include <stdio.h>

int main(int argc, char *argv[]) {
    int a = 10;
    int *ap = &a;

    printf("Endereço de a: %p\nPróximo int: %p\n", ap, ap+1);
    
    
    long l = 10;
    long *lp = &l;
    
    printf("Endereço de l: %p\nPróximo long: %p\n", lp, lp+1);
    
    return 0;
}
