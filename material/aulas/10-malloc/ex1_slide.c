#include <stdio.h>

char* retorna_str() {
  char str_vetor[32];
  str_vetor[0]='a';
  str_vetor[1]='b';
  str_vetor[2]='c';
  str_vetor[3]='d';
  str_vetor[4]='\x0';
  return str_vetor;
}
int main(){
    char *resp;
    resp = retorna_str();
    printf("%s",resp);
    return 0;
}
