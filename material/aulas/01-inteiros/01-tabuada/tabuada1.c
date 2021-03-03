#include <stdio.h>

int i;
int j;

void escreve_tabuada(int tabuada){
  int produto;

  for (i=2; i<tabuada+1; i++){
    printf("\n");
    for (j=1; j<tabuada+1; j++){
      produto = j*i;
      printf("%d ",produto);
    }
  }
}

int main(){
  int tabuada;
  
  scanf("%d", &tabuada);

  escreve_tabuada(tabuada);
  
  return 0;
}