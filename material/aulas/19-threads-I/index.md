# 19 - Concorrência e Threads

Nossa aula de hoje envolverá aprender a API `pthreads` para criação de threads e sincronização simples.

## Criando tarefas e esperando elas acabarem

O exemplo abaixo cria uma thread que roda a função `primeira_thread`, espera por seu fim e mostra a mensagem *Fim do programa*.

```c
// Funções rodadas em thread sempre tem essa assinatura
void *minha_thread(void *arg) {
    printf("Hello thread!\n");
    return NULL;
}

....
pthread_t tid;
int error = pthread_create(&tid, NULL, minha_thread, NULL);
pthread_join(tid, NULL); // espera tid acabar.
```

!!! example
    Compile o arquivo *exemplo1.c* com a flag especial `-pthread` e execute-o.

<div class="termy">

    ```console
    $ gcc exemplo1.c -o exemplo1 -pthread
    $ ./exemplo1
    ```

</div>

Vamos dissecar a chamada da função `pthread_create`:

```c
int error = pthread_create(
                           &tid, // variável para guardar ID da nova thread
                           NULL, // opções de criação. NULL = opções padrão
                           minha_thread, // função a ser executada
                           NULL // parâmetro passado para a função acima
);
```

Toda thread que rodarmos terá a seguinte assinatura (mudando, é claro, o nome da função).

```c
void *minha_thread(void *arg);
```

Uma variável do tipo `void *` representa um endereço de memória cujo conteúdo é desconhecido. Ou seja, ele diz somente onde encontrar os dados, mas não diz o que está guardado na memória naquele lugar. Este tipo de variável é usada quando queremos passar blocos de memória entre funções mas não queremos fixar um tipo de dados. Veremos com mais detalhes como isto funciona na parte 2.

!!! example
    O manual contém entradas muito bem escritas de todas as chamadas de POSIX threads que usaremos. Abra as seguintes e se familiarize com seu conteúdo.

<div class="termy">

    ```console
    $ man 7 pthreads
    $ man 3 pthread_create
    $ man 3 pthread_join
    ```

</div>

Assim como processos, threads são escalonadas pelo kernel. Isto significa que **não controlamos a ordem em que elas rodam** no nosso programa. Ou seja, ao executar `pthread_create` não sabemos se a thread principal (aquela que roda o `main`) continuará rodando ou se o controle passará instantaneamente para a nova thread. A primitiva de **sincronização** mais simples que dispomos é `pthread_join`, que garante que uma thread só prossegue quando outra acabar.

!!! exercise text short
    Retire o `pthread_join` do programa exemplo e o execute. Repita a execução várias vezes. Todas as vezes o resultado é o mesmo? O quê acontece?

    !!! answer "Resposta"
        Não. Como a `main` pode chegar no `return 0`, então o processo pode acabar sem que a thread tenha sido devidamente executada.

!!! exercise text short
    É possível que duas threads chamem `pthread_join` na mesma thread destino? Consulte o manual para saber esta resposta.

    !!! answer "Resposta"
        A resposta está disponível na seção **DESCRIPTION** ao executar `man 3 pthread_join`: *If multiple threads simultaneously try to join with the same thread...*

A resposta acima indica que precisaremos de outras primitivas de **sincronização** mais sofisticadas no futuro. Veremos isso nas próximas aulas.

!!! example
    Em um novo arquivo `.c`, crie quatro threads, cada uma executando uma função que faz um print diferente. Compile e execute seu programa várias vezes. A saída será sempre a mesma, com os printfs sempre na mesma ordem? O que está acontecendo?!

## Passando argumentos para threads

Nossas threads ainda são muito limitadas: elas não recebem nenhum argumento nem devolvem resultados. Vamos consertar isso nesta seção.

Vimos na parte 1 que o último argumento de `pthread_create` é um ponteiro para os dados que nossa função deverá receber. Neste sequência de exercícios iremos aprender a usar este argumento para passar dados para nossas threads.

Nosso primeiro exercício será feito passo a passo. Siga cada um dos passos a risca e depois responda as questões. Vamos trabalhar a partir de um arquivo vazio.

!!! example
    Crie um programa simples com uma função `main` que aloca (usando malloc) um vetor `vi` com 4 `int`s  e um vetor `tids` com 4 `pthread_t`s.

!!! example
    Adicione ao seu programa um `for` que cria 4 threads (colocando seus ids no vetor `tids`). Passe como último argumento o endereço do elemento correspondente de `vi`.

!!! example
    Espere pelo fim desta thread.

!!! example
    Crie uma função `void *tarefa_print_i(void *arg)` que declara uma variável `int *i` e dá print em seu conteúdo. Inicialize a variável `i` como mostrado abaixo:

    > `int *i = (int *) arg;`

!!! exercise text short
    Explique a utilização da variável `i` na tarefa acima.

    !!! answer "Resposta"
        Apontadores `void *` contém somente o endereço do dado, mas sem indicar seu tipo. Ao declarar `i` acima dizemos que queremos interpretar aquele endereço como o endereço de um `int`. Assim, quando fazemos `*i` conseguimos acessar o inteiro presente no endereço passado para a thread. 

Se seu programa estiver correto você deverá ver no terminal 4 prints com números de 0 a 3, cada um vindo de um thread.

!!! warning
    Se tiver problemas, valide seu código com algum colega que já tenha sido validado pelo professor. Se não tiver ninguém por perto já validado me chame ;)

!!! exercise text short
    Explique como é feita a passagem do argumento para a thread.

    !!! answer "Resposta"
        A thread recebe o endereço da respectiva posição do array alocado dinâmicamente.


!!! exercise text short
    Passamos para a thread um valor alocado dinamicamente. Por que isso é necessário?

    !!! answer "Resposta"
        Vamos discutir depois!


Vamos explorar a resposta da pergunta acima nos próximos exercícios. Para cada exercício, encontre seu problema, descreva-o usando suas próprias palavras e mostre um exemplo de saída possível. Somente depois de escrever sua resposta rode o programa.

!!! warning
    Cada exercício foca em um problema diferente. A resposta não é a mesma para ambas.

!!! exercise text medium
    Identifique um problema de escopo de dados no código abaixo (arquivo *parte2-1.c*)

    Dica: compile, execute e leia o código para tentar entender o problema!

    ```c
    void *minha_thread(void *arg) {
        int *i = (int *) arg;
        printf("Hello thread! %d\n", *i);
    }

    // dentro do main

    for (int i = 0; i < 4; i++) {
        pthread_create(&tid[i], NULL, minha_thread, &i);
    }
    ```

    !!! answer "Resposta"
        Com threads, não tenho garantir da ordem de escalonamento (não qual thread o sistema operacional vai escolher para execução, nem em qual ordem). Assim, a thread da `main` altera o valor da variável `i` e quando cada thread executa, o valor recuperado é diferente do esperado.

!!! exercise text medium
    Identifique um problema de escopo de dados no código abaixo (arquivo *parte2-2.c*)

    Dica: compile, execute e leia o código para tentar entender o problema!

    ```c
    void *minha_thread(void *arg) {
        int *i = (int *) arg;
        printf("Hello thread! %d\n", *i);
    }

    pthread_t *criar_threads(int n) {
        pthread_t *tids = malloc(sizeof(pthread_t) * n);

        for (int i = 0; i < n; i++) {
            pthread_create(&tids[i], NULL, minha_thread, &i);
        }

        return tids;
    }

    // dentro do main
        pthread_t *tids = criar_threads(4);

    ```

    !!! answer "Resposta"
        Lembra da pilha ou `stack`? Veja nos slides, cada thread tem o seu próprio espaço para guardar suas variáveis locais. Quando uma função é finalizada, o espaço alocado a ela na `stack` pode ser reutilizado. Neste exemplo, cada thread da `minha_thread` tenta ler uma variável local criada na função `criar_threads`, que pode não "existir" mais.


!!! warning
    Valide sua solução com o professor para garantir que realmente entendeu!

Agora que já entendemos como passar um argumento e que devemos sempre colocá-lo no *heap*, passar vários é muito simples: alocamos um `struct` com todos os dados que queremos enviar e passamos seu endereço no último argumento. Ao recebê-lo, a função faz um *cast* de `void *` para um ponteiro para o `struct`.

!!! example
    Modifique seu exercício do começo desta parte para receber dois argumentos do tipo inteiro e imprimir ambos valores.


## Retornando valores

Na prática, ao passar `struct`s para threads como argumentos já sabemos como retornar valores: basta adicionar um campo que própria thread deve preencher com o resultado de sua execução. Isso é equivalente a criar uma função que retorna valores em variáveis passadas por referência (ou seja, escrevendo em variáveis passadas como ponteiros).

!!! example
    Modifique seu exercício da parte anterior para que as threads retornem a multiplicação dos dois inteiros passados. Faça o print deste valor no `main`.

