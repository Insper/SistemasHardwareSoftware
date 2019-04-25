#include <stdio.h>
#include <stdlib.h>

int funcao() {
    int *num = malloc(10 * sizeof(int));
    num[0]=5;
    free(num);
    return num[0];
}

int main(int argc, char *argv[]) {
    funcao();
    return 0;
}
