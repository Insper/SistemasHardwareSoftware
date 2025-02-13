#include <stdio.h>

int main(int argc, char *argv[]) {
    int a = 10;
    int *ap = &a;

    printf("Endereço de a\t: %p\nPróximo int\t: %p sizeof %d\n", ap, ap+1, sizeof(ap));

    long l = 10;
    long *lp = &l;
    
    printf("Endereço de l\t: %p\nPróximo long\t: %p \t sizeof %d\n", lp, lp+1,sizeof(lp));
    
    return 0;
}
