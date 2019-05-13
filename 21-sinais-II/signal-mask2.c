#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void funcao_importante() {
    sleep(20);
    printf("Fim da funcao!\n");
}

int main() {
    
    printf("Entrando em funcao_importante!\n");
    printf("O programa não será interrompido até seu fim!\n");
    // bloqueie os sinais

    // libere os sinais
    printf("Tente dar Ctrl+C agora!\n");

    sleep(50);

    return 0;
}
