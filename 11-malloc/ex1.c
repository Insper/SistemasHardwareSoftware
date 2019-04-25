#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    short *vnumero;

    vnumero = malloc(sizeof(short) * 15);

    free(vnumero);

    return 0;
}
