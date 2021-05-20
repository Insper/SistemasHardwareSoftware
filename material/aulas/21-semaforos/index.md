# 21 - Semáforos

Nas última aulas aprendemos as APIs da biblioteca `pthread` para criar e esperar a finalização de threads. Também aprendemos a passar argumentos e receber de volta valores usando um `struct` alocado dinamicamente.

Usamos `mutex` quando precisamos criar regiões de **exclusão mútua** onde somente uma thread pode entrar por vez. Esta restrição é muito forte e não contempla outro caso muito comum em programação concorrente: sincronização de threads. Ou seja, o objetivo não é proteger o acesso a dados compartilhados, mas sim impor restrições no progresso das threads de maneira que elas estejam sempre em uma situação válida. Para isto trabalharemos com **semáforos**, que são um mecanismo de sincronização mais sofisticado e em geral usado para que threads sincronizem seu progresso e possam executar **em paralelo**.

**Definição**: duas tarefas podem ser feitas em paralelo se

1. elas não compartilham absolutamente nenhuma informação.
1. elas compartilham informação mas possuem **mecanismos de sincronização** de tal maneira que **toda ordem de execução possível** de suas instruções resulte no mesmo resultado final.

**Semáforos** ajudam a criar programas no segundo caso. Nesta aula iremos olhar o caso mais simples de sincronização: duas threads combinam de só progredirem quando chegarem em um certo ponto do programa.

## Rendez-vous

A expressão *Rendez-vous* significa, literalmente, *encontro* em francês. Ela é usada para marcar um horário para duas ou mais pessoas se encontrarem. No contexto de sincronização de tarefas, ele também é usado para nomear o problema de sincronização mais simples: duas threads rodando funções distintas precisam se sincronizar no meio de suas funções.

![Tarefas sincronizadas usando um RDV](rdv.svg)

As partes A e B podem ser feitas em qualquer ordem, mas ambas obrigatoriamente devem ocorrer antes de iniciar a execução de C e D. Note que C e D também podem ser feitas em qualquer ordem.

!!! warning
    Quando dizemos que duas tarefas podem ser feitas em qualquer ordem não quer dizer que elas possam ser feitas em paralelo! Apenas estamos dizendo que A inteira pode ocorrer antes ou depois de B inteira e os resultados serão os mesmos.

!!! example
    Quais das ordens de execução das partes A, B, C e D são válidas, segundo o RDV?

    - [ ] A C B D
    - [x] A B C D
    - [ ] B D A C


!!! example
    Quais das ordens de execução das partes A, B, C e D são válidas, segundo o RDV?

    - [x] B A D C
    - [ ] A D B C
    - [ ] B C A D


!!! example
    Quais das ordens de execução das partes A, B, C e D são válidas, segundo o RDV?

    - [x] A B D C
    - [ ] B D A C
    - [ ] B C A D


Vamos fazer a solução do RDV no papel primeiro.

!!! question short
    Preencha aqui quantos semáforos serão usados, seus nomes e valores iniciais.

!!! question short
    Indique onde você usaria seus semáforos para resolver o RDV.

## Semáforos POSIX

A página `sem_overview` do manual contém um resumo do uso de semáforos. A partir de seu conteúdo responda as questões abaixo.

!!! question short
    Qual o tipo de variável usada para guardar um semáforo? Quais funções são usadas para criar e destruir cada tipo de semáforo?

!!! question short
    Quais as funções usadas para incrementar e decrementar um semáforo?

!!! example
    Implemente (do zero) um programa que cria duas threads e as sincroniza usando *RDV*. Ambas deverão fazer um `print` antes e um depois do ponto de encontro. Use a imagem do começo da aula como guia.


