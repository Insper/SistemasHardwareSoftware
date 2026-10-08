// gcc eh_par.c -o eh_par
#include <stdlib.h>
#include <stdio.h>
// para visualizar o retorno do programa use:
// echo $?
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Erro!\n");
        return -1;
    }

    int num1 = atol(argv[1]);
    if (num1 >= 0) {
        return num1 % 2 == 0;
    }
        
    return -1;
}
