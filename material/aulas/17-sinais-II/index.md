# 17 - Capturando sinais

Na aula de hoje iremos criar programas que *reagem* a sinais recebidos. Já vimos que o sistema tem uma série de comportamentos padrão para cada sinal, então hoje aprenderemos a customizar esse comportamento.

!!! warning
    Apesar de muitos recursos mostrarem o uso da chamada `signal` para a captura de sinais, ela é considerada obsoleta e o recomendado é usar `sigaction`, que é um pouco mais complicada de usar mas permite maior flexibilidade ao definir o comportamento do processo.

## Capturando sinais - a chamada `sigaction`

O exemplo abaixo cria um `struct sigaction` e o seta para executar um **handler** quando o processo receber `SIGINT` (Ctrl+C).

```c
// Fora da main, criamos a função que será nosso handler
void sig_handler(int num) {
    // faz algo aqui
}

int main() {
    ....
    /* Dentro da main, uma das primeiras coisas que fazemos é
    registrar nosso handler */
    struct sigaction s;
    s.sa_handler = sig_handler; // aqui vai a função a ser executada
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;

    sigaction(SIGINT, &s, NULL);
    ....
}
```

!!! example
    Usando como exemplo o código acima, modifique o arquivo *sinal1.c* para que o programa só termine após apertar Ctrl+C três vezes. Você pode usar `exit` para sair na terceira vez. Não se esqueça de consultar `man sigaction` para verificar quais `include`s devem ser usados.

??? details "Clique para ver uma proposta de solução do exercício!"
    ```C
    #include <stdio.h>
    #include <unistd.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <sys/types.h>

    int contador = 0;

    void sig_handler(int num) {
        contador++;
        printf("Chamou Ctrl+C\n");
        if (contador == 3) {
            exit(0);
        }
    }

    int main() {
        
        struct sigaction handler;

        handler.sa_handler = sig_handler;
        handler.sa_flags = 0;
        sigemptyset(&handler.sa_mask);

        sigaction(SIGINT, &handler, NULL);
        
        printf("Meu pid: %d\n", getpid());

        while(1) {
            sleep(1);
        }
        return 0;
    }

    ```
Provavelmente sua solução para o exercício acima funciona, mas seu término não é condizente com a ação do usuário. Ao sair com `exit` o processo pai (no caso o shell) não consegue saber que o programa foi interrompido pelo usuário e acha que ele terminou normalmente. Podemos resetar o comportamento padrão de um sinal atribuindo a constante `SIG_DFL` (*signal default*) a `sigaction.sa_handler`.

!!! example
    Restaure o comportamento original no segundo *Ctrl+C*, fazendo com que o processo realmente termine com o sinal.


??? details "Clique para ver uma proposta de solução do exercício!"
    ```C
    #include <stdio.h>
    #include <unistd.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <sys/types.h>

    int contador = 0;

    void sig_handler(int num) {
        contador++;
        printf("Chamou Ctrl+C\n");
        if (contador == 2) {
            struct sigaction handler;

            handler.sa_handler = SIG_DFL;
            handler.sa_flags = 0;
            sigemptyset(&handler.sa_mask);

            sigaction(SIGINT, &handler, NULL);
        }
    }

    int main() {
        
        struct sigaction handler;

        handler.sa_handler = sig_handler;
        handler.sa_flags = 0;
        sigemptyset(&handler.sa_mask);

        sigaction(SIGINT, &handler, NULL);
        
        printf("Meu pid: %d\n", getpid());

        while(1) {
            sleep(1);
        }
        return 0;
    }
    ```


!!! exercise text short
    Podemos verificar o sinal de encerramento do último processo finalizado usando o comando`kill -l "$?"`. Execute-o e veja que realmente é `SIGINT`.

    !!! answer "Resposta"
        você deve receber no terminal uma string identificando o sinal.

Um dos problemas da solução proposta é que o último CTRL+C fica sem printf de mensagem! Para resolver o problema, vamos alterar a linha `if (contador == 3)` e fazer o processo enviar um `SIGINT` para si próprio.

??? details "Clique para ver uma proposta de solução do exercício!"
    ```C
    #include <stdio.h>
    #include <unistd.h>
    #include <signal.h>
    #include <stdlib.h>
    #include <signal.h>

    int contador = 0;

    void sig_handler(int num)
    {
        contador++;
        printf("Chamou Ctrl+C\n");
        if (contador == 3)
        {
            struct sigaction handler;

            handler.sa_handler = SIG_DFL;
            handler.sa_flags = 0;
            sigemptyset(&handler.sa_mask);

            sigaction(SIGINT, &handler, NULL);

            /*
            Envia o sinal para si mesmo.
            Outra forma: raise(SIGINT);
            */
            kill(getpid(), SIGINT);
        }
    }

    int main()
    {

        struct sigaction handler;

        handler.sa_handler = sig_handler;
        handler.sa_flags = 0;
        sigemptyset(&handler.sa_mask);

        sigaction(SIGINT, &handler, NULL);

        printf("Meu pid: %d\n", getpid());

        while (1)
        {
            sleep(1);
        }
        return 0;
    }
    ```
## Sinais e concorrência

Nesta parte vamos trabalhar com o arquivo `sinais-concorrentes.c`.

!!! example
    Leia o conteúdo do arquivo acima e complete as partes faltantes.

!!! exercise text short
    Teste sua implementação enviando sinais `SIGINT`e `SIGTERM` para seu processo. Os resultados foram os esperados?

    !!! answer "Resposta"
        Os handlers foram corretamente chamados. Mas precisamos conferir melhor o valor da variável status.

Vamos agora examinar o que acontece quando trabalhamos com vários sinais sendo recebidos ao mesmo tempo.

!!! example
    Abra dois terminais. No primeiro execute `sinais-concorrentes`.

!!! exercise text short
    No segundo terminal, realize **rapidamente** a seguinte sequência de comandos. Para cada comando, anote o que é mostrado no terminal.

    1. Envie o sinal SIGINT para o programa.
    1. Envie o sinal SIGTERM para o programa.
    1. Envie de novo SIGINT.

    !!! answer "Resposta"
        Envie `kill -s SIGINT <pid>`, `kill -s SIGTERM <pid>` e `kill -s SIGINT <pid>` e confira o resultado!

!!! exercise text medium
    Assumindo que cada função roda do começo ao fim sem interrupção, os valores da variável `status` foram os esperados? Se não, como você explica o ocorrido?

    !!! answer "Resposta"
        Não! Podemos perceber que o valor do status foi modificado sem que o primeiro handler fosse finalizado, tornando inconsistente a nossa tratativa. Isto ocorre porque a chegada de um novo sinal faz com que o handler que está executando seja interrompido e o novo handler do novo sinal passa a executar. Apenas quando este segundo handler finalizar é que o anterior continuará sua execução.

!!! warning
    Valide sua resposta com o professor antes de prosseguir. Se quiser, poderá esperar pela correção do exercício.

## Bloqueio de sinais

A principal vantagem de usarmos `sigaction` é que esta chamada permite configurar sinais a serem **bloqueados** durante a execução da função `sa_handler`. Ou seja, se um sinal bloqueado for recebido durante sua execução ele é colocado "em espera" até que `sa_handler` acabe de rodar!

!!! exercise text short
    Bloquear sinais evita o problema detectado na parte anterior?

    !!! answer "Resposta"
        Sim! Desta forma, garantimos consistência no valor da variável `status`.

!!! exercise text
    Quais sinais deverão ser bloqueados durante a execução do handler `SIGINT`? E durante a execução do handler `SIGTERM`?

    !!! answer "Resposta"
        No registro do handler de `SIGINT`, bloqueamos `SIGTERM`. No registro do handler de `SIGTERM`, bloqueamos `SIGINT`.

!!! exercise text short
    O campo `sa_mask` permite bloquear sinais enquanto os handlers executam. Consulte `man sigsetops` para ver como preenchê-lo. Escreva 
    abaixo os comandos para tal.

    !!! answer "Resposta"
        Podemos fazer, por exemplo, `sigaddset(&handler_sigterm.sa_mask, SIGINT);`

!!! example
    Modifique `sinais-concorrentes.c` para que *SIGTERM* seja bloqueado enquanto o handler de *SIGINT* roda. Repita então o experiemento acima e veja que não há mais conflito na variável global compartilhada.

!!! example O que fizemos não permite que `SIGINT` seja interrompido por um `SIGTERM`, mas permite que um `SIGTERM` seja interrompido por um `SIGINT`! Corrija esta situação.

## Exercícios para praticar

!!! exercise
    Modifique `sinal1.c` para que, ao ser colocado em background usando Ctrl+Z (SIGTSTP), imprima uma mensagem antes de parar de executar.

    **Dicas**:

    * Você precisa retornar o comportamento padrão do sinal depois de dar o print.
    * Pesquise como usar `raise` para (re)enviar um sinal para o próprio processo.


!!! exercise
    Complete o programa acima com uma outra função que imprime a mensagem *Continuando!* quando o programa voltar a rodar (sinal `SIGCONT`).

----

Uma parte importante de sinais em sistemas POSIX é que, ao interromper um processo, eles podem cancelar operações que estavam ocorrendo. Em especial, chamadas de sistema que deixam um processo bloqueado (como `wait` e `sleep`) ou que fazem operações de entrada/saída (como `read` e `write`).

!!! exercise text short
    Compile e rode o programa `sleep_longo.c`. O quê foi mostrado na tela?

!!! exercise text short
    Rode novamente o programa. Abra um novo terminal e envie um sinal `SIGTERM` para este processo. O quê é mostrado na tela? Você consegue interpretar este resultado?

    **Dicas**:

    * Será útil exibir na saída padrão o **PID** do processo!
    * Repita a execução múltiplas vezes. Vai te ajudar a entender o que acontece. Em algumas envie o sinal `SIGTERM` rapidamente, em outras, aguarde mais alguns segundos!

!!! exercise text short
    Como checamos que `sleep` realmente parou o processo por todo o tempo?

    !!! answer "Resposta"
        A resposta está no manual. Leia em especial o RETURN VALUE!
        <div class="termy">

        ```console
        $ man 3 sleep
        ```

        </div>

!!! exercise
    Modifique o programa para que ele chame `sleep` tanto quanto for necessário para que o processo durma o tempo especificado. Salve este arquivo como `sleep_longo_while.c`.

!!! exercise
    Troque o código de `sleep_longo.c` para ignorar o sinal `SIGTERM`. O programa agora funciona como esperado? Por que?
