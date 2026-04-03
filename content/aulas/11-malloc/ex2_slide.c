// para compilar use
// gcc -g ex2_slide.c -o ex2_slide 
// para executar use:
// ./ex2_slide
// Para executar o valgrind
// valgrind --leak-check=yes ./ex2_slide

#include <stdio.h>
#include <stdlib.h>

int main() {
  int i, n, *p;
  
  scanf("%d",&n); // le tamanho do vetor

  /* aloca n*sizeof(int) bytes no heap */
  p = (int *) malloc(n * sizeof(int));
  if (p == NULL) {
    perror("malloc");
    exit(0);
  }
  /* inicializa o vetor, o que acontece se nao inicializar o vetor ?*/
  for (i = 0; i <= n; i++) {
    p[i] = i;
  }
  // imprime o vetor
  for (i = 0; i <= n; i++) {
    printf("%d ",p[i]);
  }
  /* libera a memória alocada */
  free(p);
}