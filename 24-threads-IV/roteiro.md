---
title: 24 - POSIX Threads IV
author: Igor Montagner
...

# Parte 1 - entrega

**Exercício**: Nossa atividade final é a implementação de um modelo produtor-consumidor 1-1. Esse modelo é interessante pois permite ganhos de desempenho com uma implementação relativamente simples. Seu trabalho será

1. Rodar `producer` e `consumer` cada um em uma thread separada. Note que será necessário modificá-las para que, agora, cada uma produza os `N` itens feitos na versão original. Você pode supor que esse `N` é conhecido por ambas threads e não muda.
1. Sincronizar ambas threads para que
    1. a função `consumer` espere a função `producer` criar um novo `prod_result` para processá-lo.
    1. a função `producer` espere a função `consumer` acabar de processar o item atual para enviar um novo item.
1. Para fazer o item anterior você precisará definir quantas e quais variáveis serão compartilhadas entre as duas threads.
1. Também será importante definir quantos e quais semáforos e mutexes serão usados no seu programa.
1. Seu programa deverá ter a mesma saída que o anterior.

