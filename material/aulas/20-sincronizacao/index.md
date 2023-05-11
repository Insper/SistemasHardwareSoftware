# 20 - Sincronização com Mutex

Na última aula aprendemos as APIs da biblioteca `pthread` para criar e esperar a finalização de threads. Também aprendemos a passar argumentos e receber de volta valores usando um `struct` alocado dinamicamente.

## Aquecimento

Vamos iniciar uma revisão trabalhando em cima do arquivo `soma_global.c`.

!!! example
    Abra o arquivo e analise seu conteúdo.

!!! exercise text short
    Qual o papel da função `soma_parcial`?  Explique o papel de cada atributo de `struct soma_parcial_args`.

    !!! answer "Resposta"
        Soma parte de um array (alguns elementos). Nos argumentos, o `*vetor` representa um ponteiro para todos os elementos do array. Já `start` e `end` representam o range de posições as quais queremos somar. 

!!! exercise text short
    Como você setaria os atributos de `struct soma_partical_args` para obter a soma do vetor todo? E para obter somente a soma da primeira metade do vetor?

    !!! answer "Resposta"
        ```
        args->vetor = vetor;
        args->start = 0;
        args->end = n;
        ```

Para fins didáticos, estamos atualizando diretamente a variável `soma_total` dentro do `for`.

!!! example
    Complete as partes faltantes e rode o programa. Ele dá os resultados esperados? Teste para valores de `n` incrementalmente maiores.

!!! exercise text short
    Os resultados acima estarão errados. Você consegue explicar por que?

    !!! answer "Resposta"
        Na operação `soma = soma + spa->vetor[i];` a variável global `soma` está sendo lida, somada e posteriormente atribuída a ela própria. Entretando, entre a leitura e a atribuição, outra thread pode atualizar o valor da `soma`, tornando os resultados inconsistentes e imprevisíveis.

## Sincronização usando `mutex`

Vamos agora trabalhar agora para corrigir este erro! Lembrando da aula, as operações possíveis são as seguintes:

* `lock` - se tiver destravado, trava e continua; se não estiver espera.
* `unlock` - se tiver a trava, a destrava e permite que outras tarefas travem.

Note que não existe garantia de ordem! Ou seja, se tiverem vários processos esperando por um `mutex` qualquer um deles pode receber o acesso. Inclusive, uma thread pode esperar "para sempre" e nunca receber o acesso. Não é provável, mas é possível.

!!! warning
    Você pode precisar instalar o pacote `manpages-posix-dev` para obter as páginas do manual usadas neste roteiro.

<div class="termy">

    ```console
    $ sudo apt update
    $ sudo apt install manpages-posix-dev
    ```

</div>

!!! exercise text short
    Identifique no seu código quais linhas compõe a região crítica e onde deveriam estar as diretivas `lock` e `unlock`. Escreva abaixo suas concluões.

    !!! answer "Resposta"
        Onde a `soma` está sendo atualizada. Damos lock antes e unlock depois da linha `soma = soma + spa->vetor[i];`

!!! example
     Coloque um comentário nas linhas identificadas acima.

Já sabemos onde iremos colocar as operações de `lock` e `unlock` do mutex. Agora falta só criá-lo.

!!! exercise text short
    O mutex precisa ser criado e inicializado. Onde isto deve ser feito? Como ele pode ser recebido pela função da thread?

    !!! answer "Resposta"
        Podemos fazer isto na função `main`, antes da criação das threads. Para que ele seja recebido pela função, podemos criar um outro argumento na nossa `struct soma_parcial_args`!

!!! exercise text short
    Consulte o manual de `pthread_mutex_init` e escreva abaixo como criar e inicializar um mutex.

    !!! answer "Resposta"
        Podemos fazer, por exemplo:
        ```c
        pthread_mutex_t mutex_soma = PTHREAD_MUTEX_INITIALIZER;
        ```


!!! exercise text short
    Consulte o manual de `pthread_mutex_lock` e `pthread_mutex_unlock` e escreva abaixo como usá-las.

    !!! answer "Resposta"
        ```c
        pthread_mutex_lock(<mutex_address>);
        // Faça sua operação!
        pthread_mutex_unlock(<mutex_address>);
        ```

!!! example
    Com base nas suas respostas acima, conserte seu programa `soma_global.c` e verifique que ele retorna os resultados corretos.

!!! exercise text short
    Agora meça o tempo de execução e anote abaixo. Compare com o original (que não funcionava) e explique a diferença.

    !!! answer "Resposta"
        Podemos conferir utilizando o comando `time` no terminal. Percebemos um aumento no tempo com o uso do mutex. Isto ocorre devido a necessidade de sincronizar o acesso à variável global `soma`.

<div class="termy">

    ```console
    $ time soma_global_v1 < in2.txt
    $ time soma_global_v2 < in2.txt
    ```

</div>

!!! tip
    Usar `mutex` é muito caro! Além de acabar com o paralelismo, as operações `lock` e `unlock` também são custosas.

## Economizando `mutex`

Nesta parte final iremos ver como diminuir o número de chamadas ao `mutex`.

!!! exercise text short
    É necessário atualizar a variável global `soma` a cada iteração do `for`? E é possível atualizá-la somente uma vez por thread?

    !!! answer "Resposta"
        Podemos criar uma variável local que acumula a soma e só atualiza `soma_global` no fim. Seria uma variável por thread!

!!! example
    Implemente a ideia acima e veja se houve melhora. Salve como `soma-global2.c`.

O exercício acima deverá ter desempenho bom, já que limitamos a quantidade de vezes que usamos o `mutex`. Vamos tentar outra ideia agora.

!!! exercise text  short
    Precisamos da variável global? E se cada thread retornasse sua soma parcial? Como o programa poderia ser organizado para que essa ideia funcione?

    !!! answer "Resposta"
        Cada thread poderia retornar na struct de argumentos o resultado de sua soma. Na função main, após cada reposta de conclusão da thread (retorno da `pthread_join`), poderíamos somar os resultados.

!!! exercise text short
    A ideia acima precisou de `mutex`? Por que?

    !!! answer "Resposta"
        Não, pois na função `main` a execução da soma seria sequencial.

!!! example
    Implemente a ideia acima e confira os resultados. Houve melhora no desempenho?


