# 17 - Capturando sinais

Na aula de hoje iremos criar programas que *reagem* a sinais recebidos. Já vimos que o sistema tem uma série de comportamentos padrão para cada sinal, então hoje aprenderemos a customizar esse comportamento.

!!! warning
    Apesar de muitos recursos mostrarem o uso da chamada `signal` para a
    captura de sinais, ela é considerada obsoleta e o recomendado é usar
    `sigaction`, que é um pouco mais complicada de usar mas permite maior flexibilidade ao definir o comportamento do processo.

## Capturando sinais - a chamada `sigaction`

O exemplo abaixo cria um `struct sigaction` e o seta para executar um handler quando o processo receber `SIGINT` (Ctrl+C).

~~~{.c}
void sig_handler(int num) {
    // faz algo aqui
}

....
struct sigaction s;
s.sa_handler = sig_handler; // aqui vai a função a ser executada
sigemptyset(&s.sa_mask);
s.sa_flags = 0;

sigaction(SIGINT, &s, NULL);
~~~

!!! example
    Usando como exemplo o código acima, modifique o arquivo *sinal1.c* para que o programa só termine após apertar Ctrl+C três vezes. Você pode usar `exit` para sair na terceira vez. Não se esqueça de consultar `man sigaction` para verificar quais `include`s deve ser usados.

O programa acima funciona, mas seu término não é condizente com a ação do usuário. Ao sair com `exit` o processo pai (no caso o shell) não consegue saber que o programa foi interrompido pelo usuário e acha que ele terminou normalmente. Podemos resetar o comportamento padrão de um sinal atribuindo a constante `SIG_DFL` (*signal default*) a `sigaction.sa_handler`.

!!! example
    Restaure o comportamento original no segundo *Ctrl+C*, fazendo com que o processo realmente termine com o sinal.

!!! question short
    Podemos verificar o sinal que terminou um processo usando o comando `kill -l "$?"`. Execute-o e veja que realmente é `SIGINT`.

## Sinais e concorrência

Nesta parte vamos trabalhar com o arquivo `sinais-concorrentes.c`.

!!! example
    Leia o conteúdo do arquivo acima e complete as partes faltantes.

!!! question short
    Teste sua implementação enviando sinais `SIGINT`e `SIGTERM` para seu processo. Os resultados foram os esperados?

Vamos agora examinar o que acontece quando trabalhamos com vários sinais sendo recebidos ao mesmo tempo.

!!! example
    Abra dois terminais. No primeiro execute `sinais-concorrentes`.

!!! question short
    No segundo terminal, realize a seguinte sequência de comandos. Para cada comando, anote o que é mostrado no terminal.

    1. Envie o sinal SIGINT para o programa.
    1. Envie o sinal SIGTERM para o programa.
    1. Envie de novo SIGINT.

!!! question medium
    Assumindo que cada função roda do começo ao fim sem interrupçãom, os valores da variável `status` foram os esperados? Se não, como você explica o ocorrido?

!!! warning
    Valide sua resposta com o professor antes de prosseguir. Se quiser, poderá esperar pela correção do exercício.

## Bloqueio de sinais

A principal vantagem de usarmos `sigaction` é que esta chamada permite configurar sinais a serem **bloqueados** durante a execução da função `sa_handler`. Ou seja, se um sinal bloqueado for recebido durante sua execução ele é colocado "em espera" até que `sa_handler` acabe de rodar!

!!! question short
    Bloquear sinais evita o problema detectado na parte anterior?

!!! question
    Quais sinais deverão ser bloqueados durante a execução do handler `SIGINT`? E durante a execução do handler `SIGTERM`?

!!! question short
    O campo `sa_mask` permite bloquear sinais enquanto os handlers executam. Consulte `man sigsetops` para ver como preenchê-lo. Escreva abaixo os comandos para tal.

!!! example
    Modifique `sinais-concorrentes.c` para que *SIGTERM* seja bloqueado enquanto o handler de *SIGINT* roda. Repita então o experiemento acima e veja que não há mais conflito na variável global compartilhada.

!!! example O que fizemos não permite que `SIGINT` seja interrompido por um `SIGTERM`, mas permite que um `SIGTERM` seja interrompido por um `SIGINT`! Corrija esta situação.


<!--
# Exercícios para praticar

**Exercício:** Modifique `sinal1.c` para que, ao ser colocado em background usando
Ctrl+Z (SIGTSTP), imprima uma mensagem antes de parar de executar.

**Dicas**:

* Você precisa retornar o comportamento padrão do sinal depois de dar o print.
* Pesquise como usar `raise` para (re)enviar um sinal para o próprio processo.

**Exercício**: Complete o programa acima com uma outra função que imprime a mensagem *Continuando!* quando o programa voltar a rodar (sinal `SIGCONT`).

----

Uma parte importante de sinais em sistemas POSIX é que, ao interromper um processo, eles podem cancelar operações que estavam ocorrendo. Em especial, chamadas de sistema que deixam um processo bloqueado (como `wait` e `sleep`) ou que fazem operações de entrada/saída (como `read` e `write`).

**Exercício**: compile e rode o programa `sleep_longo.c`. O quê foi mostrado na tela?

**Exercício**: Rode novamente o programa. Abra um novo terminal e envie um sinal `SIGTERM` para este processo. O quê é mostrado na tela? Você consegue interpretar este resultado?

**Exercício**: Como checamos que `sleep` realmente parou o processo por todo o tempo?

**Exercício**: Modifique o programa para que ele chame `sleep` tanto quanto for necessário para que o processo durma o tempo especificado. Salve este arquivo como `sleep_longo_while.c`.

**Exercício**: Troque o código de `sleep_longo.c` para ignorar o sinal `SIGTERM`. O programa agora funciona como esperado? Por que?
-->
