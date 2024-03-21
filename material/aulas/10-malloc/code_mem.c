#include <stdio.h>
#include <stdlib.h>
/* 1L << 28 = 256 MB */
/* 1L << 10 = 1 MB */
/* 1L << 22 = 4 MB */
/* 1L << 31 = 2 GB */
/* 1L << 32 = 4 GB */



char huge_array[1L<<33]; /* 1L<<31 2 GB */

int main(int argc, char *argv[]) {
    char big_array[1L<<22];  /* 1L<<23 = 8 MB */

    void *p1;
    int local = 0;
    p1 = malloc(1L << 32); /* 1L << 32 = 4 GB */
    /* Some print statements ... */
    printf("&p1 = %p, p1 = %p\n",&p1,p1);
    printf("   big_array = %p\n",big_array);
    printf("  huge_array = %p\n",huge_array);
    printf("       local = %d\n",local);

    return 0;
}

