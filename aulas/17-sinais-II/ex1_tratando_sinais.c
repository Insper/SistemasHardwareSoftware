// gcc ex1_tratando_sinais.c -o ex1 
#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void trata_falha_memoria(int num){
  printf("Falha no acesso a memoria!!.\n"); 
	printf("Vou esperar 1 segundo para sair;\n");
  sleep(1);
  exit(0); // o que acontece se tirar exit(0) ?
}
int main()
{ // Preenche estrutura para capturar SIGSEGV
  struct sigaction sa;
  sa.sa_handler = trata_falha_memoria;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGSEGV,&sa, NULL);
  // Forca falha de segmentacao
  int *px = (int*) 0x01010101;
	*px = 0;
  printf("fim do programa.\n");
  return 0;
}

