#include <stdio.h>
#include <stdlib.h>

/*
 * Aloca a matriz utilizando alocacao dinamica
 * e ponteiros para ponteiros.
 */
int **alocar(int nlin, int ncol) {

}

/*
 * Exibe, na saida padrao, os valores armazenados na matriz.
 */
void exibir(int **mat,  int nlin, int ncol) {

}
 
/*
 * Le valores da entrada padrao e armazena na matriz.
 */
void ler(int **mat, int nlin, int ncol) {

}

/*
 * Soma todos os valores armazenados na matriz.
 */
int somar(int **mat, int nlin, int ncol) {
    return 0;
}

int main(int argc, char *argv[]) {
    int nlin, ncol;
    int **mat;

    scanf("%d %d", &nlin, &ncol);

    mat = alocar(nlin, ncol);

    ler(mat, nlin, ncol);
    exibir(mat, nlin, ncol);

    printf("Soma: %d\n", somar(mat, nlin, ncol));

    return 0;
}
