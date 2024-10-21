# 16 - Enviando sinais

Na aula de hoje falamos sobre sinais e vimos que grande parte deles indica que algo excepcional aconteceu. Veremos neste handout as chamadas usadas para consultar o status de um processo quando ele acaba com erro e como enviar sinais para outros processos.

## Recuperando informações de erros usando `wait`

Anteriormente vimos que ao chamar `wait(&status);` guardamos informações sobre o fim do processo filho na variável `status`. Nos outros exercícios olhamos para os casos em que `WIFEXITED(status) == 1`.

```C
int wstatus;

wait(&wstatus);
printf("Filho acabou\n");

// Utiliza macro para ler um "pedaço" (um ou mais bits) de wstatus
printf("Terminou normal?: %d\n", WIFEXITED(wstatus)); // lê 0 ou 1

// se terminou normalmente
if (WIFEXITED(wstatus)) {
    // lê o byte menos significativo do return do filho
    printf("Valor de retorno: %d\n", WEXITSTATUS(wstatus));
}
```

Todo término inesperado de um programa em execução (processo) é feito usando um sinal. Ao acessar informações em um local de memória não mapeado para o nosso processo ele recebe o sinal `SIGSEGV`. Ao executar uma divisão por zero ele receberá o sinal `SIGFPE`. Logo, nestes casos é verdade que `WIFSIGNALED(status) == 1`, então podemos pegar o número do sinal usando a macro `WTERMSIG(status)`.

!!! exercise text short
    Leia o arquivo *parte1.c*. O que ele faz? Quantos processos são criados (conte o original)?

    !!! answer "Resposta"
        O programa original cria um processo filho, que faz uma divisão por zero. São dois processos, portanto.

!!! example
    Modifique *parte1.c* para o processo pai esperar o fim do filho e mostrar uma mensagem com o `pid` do filho que acabou (pegue isto via `wait`).

!!! example
    No proceso pai, após o `wait` mostre no terminal as seguintes expressões:

    * `WIFEXITED(status)`
    * `WIFSIGNALED(status)`
    * `WTERMSIG(status)`


!!! example "To-Do"
    Mostrar o número do sinal não é muito útil. Pesquise sobre a chamada `strsignal` e use-a para mostrar uma mensagem descritiva de qual sinal foi recebido no exercício acima.

!!! tip
    Após cada modificação no código, compile e execute para conferir os resultados!

## Envio de sinais via terminal

Além de erros e exceções, sinais também são usados para avisar de mudanças no sistema, sejam elas iniciadas pelo usuário ou por outros processos. A sequência de exercícios abaixo é um experimento de envio de sinais.


!!! example
    Faça uma cópia do arquivo *parte1.c* e salve como *parte2.c*. No novo arquivo, altere para que o processo filho mostre seu pid e entre em loop infinito.

Claramente nem o pai nem o filho terminam no exemplo acima. Porém, se o filho terminar o pai termina também! O sinal **SIGKILL** é usado para terminar forçadamente um processo e ele pode ser enviado por qualquer outro processo do mesmo usuário (ou o *root*, que pode mandar sinais para qualquer processo do sistema).

O envio de sinais é feito usando a chamada `kill`. Assim como outras chamadas de sistema, `kill` possui também um programa de linha de comando.

!!! example
    Abra dois terminais e coloque um ao lado do outro. No primeiro, execute o programa *parte2.c*.

!!! example
    No segundo terminal, use a ferramenta de linha de comando `kill` para enviar o sinal **SIGKILL** para o processo filho. Se precisar, consulte a documentação usando `man 1 kill`.

!!! exercise text short
    Use `man 7 signal` para ver a lista de sinais disponíveis e seus números. Qual seria o número para o sinal `SIGINT`?

    !!! answer "Resposta"
        Execute `man 7 signal`e procure por **Signal numbering for standard signals**

Isto deve ter feito o pai finalizar e mostrar a informação de que o processo filho foi finalizado. Note que o pai tem direito a saber o sinal usado para finalizar um filho:

!!! example
    Envie o sinal `SIGINT` para seu processo filho e verifique que o processo pai mostra o número correto.

## Envio de sinais em um programa

O programa `kill` é apenas um casquinha em volta de sua chamada de sistema.

!!! example
    Veja a documentação da chamada de sistema (em C) no manual `man 2 kill`

!!! example
    Faça uma cópia do arquivo *parte2.c* e salve como *parte3.c*. Modifique o novo arquivo para que o processo pai espere 10 segundos e envie um **SIGKILL** para o filho.

!!! exercise text short
    Agora os dois processos acabam? As informações de finalização no pai condizem com o sinal enviado?

    !!! answer "Resposta"
        Se restarem dúvidas, confira com o professor!

### Extra

Até o momento usamos a chamada `wait` para esperar um processo filho acabar. Porém, não sabemos ainda checar **se** um processo filho acabou (um processo filho específico, sem necessariamente deixar a chamada `wait` travada)! Podemos fazer isso com a função `waitpid`, que recebe o `pid_t` do processo filho, e permite esperar ou não pela finalização dele.

!!! example
    Pesquise no manual pela flag `WNOHANG` da chamada `waitpid`.

!!! example
    Faça uma cópia do arquivo *parte3.c* e salve como *parte4.c*. Modifique o novo arquivo para que o processo pai só envie o sinal se o processo filho ainda estiver executando. Salve como *parte4.c*

