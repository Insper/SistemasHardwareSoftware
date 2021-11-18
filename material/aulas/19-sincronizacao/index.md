# 19 - Sincronização com Mutex

Na última aula aprendemos as APIs da biblioteca `pthread` para criar e esperar a finalização de threads. Também aprendemos a passar argumentos e receber de volta valores usando um `struct` alocado dinamicamente.

## Aquecimento

Vamos iniciar uma revisão trabalhando em cima do arquivo `soma_global.c`.

!!! example
    Abra o arquivo e analise seu conteúdo.

!!! question short
    Qual o papel da função `soma_parcial`?  Explique o papel de cada atributo de `struct soma_parcial_args`.

!!! question short
    Como você setaria os atributos de `struct soma_partical_args` para obter a soma do vetor todo? E para obter somente a soma da primeira metade do vetor?

Para fins didáticos, estamos atualizando diretamente a variável `soma_total` dentro do `for`.

!!! example
    Complete as partes faltantes e rode o programa. Ele dá os resultados esperados? Teste para valores de `n` incrementalmente maiores.

!!! question short
    Os resultados acima estarão errados. Você consegue explicar por que?

## Sincronização usando `mutex`

Vamos agora trabalhar agora para corrigir este erro! Lembrando da aula, as operações possíveis são as seguintes:

* `lock` - se tiver destravado, trava e continua; se não estiver espera.
* `unlock` - se tiver a trava, a destrava e permite que outras tarefas travem.

Note que não existe garantia de ordem! Ou seja, se tiverem vários processos esperando por um `mutex` qualquer um deles pode receber o acesso. Inclusive, uma thread pode esperar "para sempre" e nunca receber o acesso. Não é provável, mas é possível.

!!! warning
    Você pode precisar instalar o pacote `manpages-posix-dev` para obter as páginas do manual usadas neste roteiro.

!!! question short
    Identifique no seu código quais linhas compõe a região crítica e onde deveriam estar as diretivas `lock` e `unlock`. Escreva abaixo suas concluões.

!!! example
     Coloque um comentário nas linhas identificadas acima.

Já sabemos onde iremos colocar as operações de `lock` e `unlock` do mutex. Agora falta só criá-lo.

!!! question short
    O mutex precisa ser criado e inicializado. Onde isto deve ser feito? Como ele pode ser recebido pela função da thread?

!!! question short
    Consulte o manual de `pthread_mutex_init` e escreva abaixo como criar e inicializar um mutex.


!!! question short
    Consulte o manual de `pthread_mutex_lock` e `pthread_mutex_unlock` e escreva abaixo como usá-las.

!!! example
    Com base nas suas respostas acima, conserte seu programa `soma_global.c` e verifique que ele retorna os resultados corretos.

!!! question short
    Agora meça o tempo de execução e anote abaixo. Compare com o original (que não funcionava) e explique a diferença.

!!! tip
    Usar `mutex` é muito caro! Além de acabar com o paralelismo, as operações `lock` e `unlock` também são custosas.

## Economizando `mutex`

Nesta parte final iremos ver como diminuir o número de chamadas ao `mutex`.

!!! question short
    É necessário atualizar a variável global `soma` a cada iteração do `for`? E é possível atualizá-la somente uma vez por thread?

    !!! details
        Podemos criar uma variável local que acumula a soma e só atualiza `soma_global` no fim.

!!! example
    Implemente a ideia acima e veja se houve melhora. Salve como `soma-global2.c`.

O exercício acima deverá ter desempenho bom, já que limitamos a quantidade de vezes que usamos o `mutex`. Vamos tentar outra ideia agora.

!!! question  short
    Precisamos da variável global? E se cada thread retornasse sua soma parcial? Como o programa poderia ser organizado para que essa ideia funcione?

!!! question short
    A ideia acima precisou de `mutex`? Por que?

!!! example
    Implemente a ideia acima e confira os resultados. Houve melhora no desempenho?


