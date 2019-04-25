#include <stdio.h>
#include <stdlib.h>

int funcao() {
    int *num = malloc(10 * sizeof(int));
    num[0]=5;
    printf("Libera!\n");
    free(num);
    free(num);
    printf("Terminou!\n");
    return 0;
}

int main(int argc, char *argv[]) {
    funcao();
    return 0;
}
