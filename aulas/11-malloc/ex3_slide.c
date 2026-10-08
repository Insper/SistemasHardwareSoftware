#include <stdlib.h>
#include <stdio.h>

char big_array[1L<<24];  /* 16 MB */
char huge_array[1L<<31]; /*  2 GB */

int global = 0;

int useless() { return 0; }

int main()
{
    void *p1, *p2, *p3, *p4;
    int local = 0;
    p1 = malloc(1L << 28); /* 256 MB */
    p2 = malloc(1L << 8);  /* 256  B */
    p3 = malloc(1L << 32); /*   4 GB */
    //p4 = malloc(1L << 8);  /* 256  B */
    /* Some print statements ... */
    printf("programa terminado normalmente.\n");
    return 0;
}