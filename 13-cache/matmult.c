#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float *data;
    int m, n;
} matriz;


matriz *cria_matriz(int m, int n) {
    float *data;
    matriz *M;
    data = malloc(sizeof(float) * m * n);
    if (data == NULL) {
        printf("Erro na alocação de memória\n");
        exit(-1);
    }
    
    M = malloc(sizeof(matriz));
    if (M == NULL) {
        printf("Erro na alocação de memória\n");
        exit(-1);
    }

    M->m = m;
    M->n = n;
    M->data = data;
    return M;
}

matriz *le_matriz(char *path) {
    FILE *f;
    matriz *M;
    int m, n, i, j;
    float *data;
    f = fopen(path, "r");
    if (f == NULL) {
        printf("Arquivo não encontrado: %s\n", path);
        exit(-1);
    }
    fscanf(f, "%d %d", &m, &n);
    M = cria_matriz(m, n);
    data = M->data;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            fscanf(f, "%f", &(data[i * n + j]));
        }
    }
    return M;    
}

void print_matriz(matriz *mat) {
    int i, j, m, n;
    float *data;
    m = mat->m;
    n = mat->n;
    data = mat->data;
    printf("%d %d\n", m, n);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%f ", data[i * n + j]);
        }
        printf("\n");
    }
}


#ifdef INGENUO
matriz *matmult (matriz *A, matriz *B) {
    int i, j, k;
    matriz *C;
    C = cria_matriz(A->m, B->n);

    for (i = 0; i < A->m; i++) {
        for (j = 0; j < C->n; j++) {
            C->data[i*C->n + j] = 0;
        }
    }

    for (i = 0; i < A->m; i++) {
        for (j = 0; j < C->n; j++) {            
            for (k = 0; k < A->n; k++) {
                C->data[i*C->n + j] += A->data[i*A->n + k] * B->data[k*C->n + j];
            }
        }
    }
    return C;
}
#endif

int main(int argc, char *argv[]) {
    matriz *A, *B, *C;

    if (argc < 3) {
        printf("Uso: matmul A B\n");
        return -1;
    }

    A = le_matriz(argv[1]);
    B = le_matriz(argv[2]);
    C = matmult(A, B);
    print_matriz(C);
    return 0;
}

