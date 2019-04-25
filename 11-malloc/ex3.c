#include <stdio.h>
#include <stdlib.h>

void funcao() {
    char *txt = malloc(100 * sizeof(char));
    txt[0]='A';
    txt[1]='\n';
}

int main(int argc, char *argv[]) {
    funcao();
    return 0;
}
