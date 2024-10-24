#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int b=0;
void trata_div_by_zero(int num){
  // num = numero do sinal 
	printf("Divisao por zero!!.\n"); 
	printf("Vou esperar pra sair;\n");
  sleep(1);
  exit(0);
}
int main()
{
  struct sigaction sig_div_by_zero;
  sig_div_by_zero.sa_handler = trata_div_by_zero;
  sig_div_by_zero.sa_flags = 0;
  sigemptyset(&sig_div_by_zero.sa_mask);
  sigaction(SIGFPE,&sig_div_by_zero, NULL);
  int i = 3/b;
  printf("fim do programa.\n");
  return 0;
}

