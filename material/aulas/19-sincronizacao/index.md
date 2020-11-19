# 19 - Sincronização

Na última aula aprendemos as APIs da biblioteca `pthread` para criar e esperar a finalização de threads. Também aprendemos a passar argumentos e receber de volta valores usando um `struct` alocado dinamicamente. 

## Aquecimento

Vamos iniciar uma revisão trabalhando em cima do arquivo `soma_global.c`. 

!!! example
    Abra o arquivo e analise seu conteúdo.

!!! question short
    Qual o papel da função `soma_parcial`?  Explique o papel de cada atributo de 

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

!!1 example
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
    É necessário atualizar a variável global `soma` a cada iteração do `for`? E é possível atualizá-la somente uma vez?
    
!!! example
    Implemente a ideia acima e veja se houve melhora. Salve como `soma-global2.c`.

O exercício acima deverá ter desempenho bom, já que limitamos a quantidade de vezes que usamos o `mutex`. Vamos tentar outra ideia agora.

!!! question  short
    Precisamos da variável global? E se cada thread retornasse sua soma parcial? Como o programa poderia ser organizado para que essa ideia funcione? 

!!! question short
    A ideia acima precisou de `mutex`? Por que?

!!! example
    Implemente a ideia acima e confira os resultados. Houve melhora no desempenho?  


<!--
# Parte 2 - semáforos

Usamos `mutex` quando precisamos criar regiões de **exclusão mútua** onde somente uma thread pode entrar por vez. Esta restrição é muito forte e não contempla outro caso muito comum em programação concorrente: sincronização de threads. Ou seja, o objetivo não é proteger o acesso a dados compartilhados, mas sim impor restrições no progresso das threads de maneira que elas estejam sempre em uma situação válida. Para isto trabalharemos com **semáforos**, que são um mecanismo de sincronização mais sofisticado e geral usado para que threads sincronizem seu progresso e possam executar **em paralelo**.

**Definição**: duas tarefas podem ser feitas em paralelo se

1. elas não compartilham absolutamente nenhuma informação.
1. elas compartilham informação mas possuem **mecanismos de sincronização** de tal maneira que **toda ordem de execução possível** de suas instruções resulte no mesmo resultado final.

**Semáforos** ajudam a criar programas no segundo caso. Nesta aula iremos olhar o caso mais simples de sincronização: duas threads combinam de só progredirem quando chegarem em um certo ponto do programa.

## Rendez-vous

A expressão *Rendez-vous* significa, literalmente, *encontro* em francês. Ela é usada para marcar um horário para duas ou mais pessoas se encontrarem. No contexto de sincronização de tarefas, ele também é usado para nomear o problema de sincronização mais simples: duas threads rodando funções distintas precisam se sincronizar no meio de suas funções.

![Tarefas sincronizadas usando um RDV](rdv.svg){width=400px}

As partes A e B podem ser feitas em qualquer ordem, mas ambas obrigatoriamente devem ocorrer antes de iniciar a execução de C e D. Note que C e D também podem ser feitas em qualquer ordem.

<div class="alert"> Quando dizemos que duas tarefas podem ser feitas em qualquer ordem não quer dizer que elas possam ser feitas em paralelo! Apenas estamos dizendo que A inteira pode ocorrer antes ou depois de B inteira e os resultados serão os mesmos.  </div>

\newpage

**Exercício**: Marque abaixo as ordens de execução possíveis para as partes A, B, C e D.

1. A C B D
1. A B C D
1. B D A C
1. B A D C
1. B A C D

Vamos fazer a solução do RDV no papel primeiro.

**Inicialização**: Preencha aqui quantos semáforos serão usados, seus nomes e valores iniciais. \vspace{3em}

**Sua solução**: Indique abaixo em quais quadrados azuis você usaria seus semáforos para resolver o RDV. Você pode usar mais de um semáforo em um mesmo quadrado e pode deixar os outros vazios.

## Semáforos POSIX

A página `sem_overview` do manual contém um resumo do uso de semáforos. A partir de seu conteúdo responda as questões abaixo.

**Exercício**: Qual o tipo de variável usada para guardar um semáforo? Quais funções são usadas para criar e destruir cada tipo de semáforo? \vspace{5em}

**Exercício**: Quais as funções usadas para incrementar e decrementar um semáforo? \vspace{5em}

**Exercício**: Implemente (do zero) um programa que cria duas threads e as sincroniza usando *RDV*. Ambas deverão fazer um `print` antes e um depois do ponto de encontro.

# Parte 3 - Entrega

**Exercício**: adapte o exercício da soma do vetor para calcular também a variância. Percebam que agora temos duas partes que tem uma relação de dependência:

1. Computar a soma (divida em duas partes)
1. Computar a variância (que depende da soma)

Use *RDV* para sincronizar as duas threads e você deverá implementar tudo na função

```
void *computa_media_variancia(void *)
```

Salve sua solução em um arquivo `var1.c` e entregue via blackboard.
-->
