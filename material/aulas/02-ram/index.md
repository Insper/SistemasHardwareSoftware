# 02 - Representação de dados em RAM

## Experimentos

Vamos trabalhar com os arquivos `experimento0-4.c`. Compile e execute cada um deles e coloque suas saídas abaixo. Comente os resultados comparando os valores das constantes no código em *C* e a saída dos programas.

Para compilar cada `.c`, utilize:

<div class="termy">

```console
$ gcc -Wall -pedantic experimento0.c -o e0
```

</div>

!!! question medium
    Examine o código *C* do arquivo *experimento0.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.

!!! question medium
    Examine o código *C* do arquivo *experimento1.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.

!!! question medium
    Examine o código *C* do arquivo *experimento2.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.

!!! question medium
    Examine o código *C* do arquivo *experimento3.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.

!!! question medium
    Examine o código *C* do arquivo *experimento4.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.


## Representação de `struct` em *RAM*

A utilização de `struct` junta tudo que já vimos sobre representação de todos os tipos de dados na memória. Não se esqueça de levar em conta as questões de alinhamento mostradas na parte expositiva da aula.


!!! warning
    Você **não** deverá abrir o código de `parte1.c`. Ele está no repositório para você poder conferir suas respostas.


!!! example
    Compile e execute _parte1.c_.


!!! example
    Os endereços mostrados na saída de `parte1` pertencem a um só struct declarado como `struct player one`. Quais são os tamanhos de cada campo?

    **Dica**: pode não ser possível identificar *exatamente* o tamanho de cada campo, mas é esperado que você identifique ao menos o tamanho **máximo** de cada um.

!!! example
    A segunda parte da saída de `parte1` mostra os endereços de cada campo do struct. Note que `&one` e ` &one.icon` são iguais. Você consegue explicar por que? Se não, volte na aula expositiva e reveja a parte sobre `struct` e alinhamento de memória.

!!! question medium
    Baseado nas respostas acima, declare abaixo o `struct`. Escreva-o da mesma maneira que usaria em um programa em *C*.

!!! warning "Confira suas respostas com _parte1.c_. "

## Examinando a execução de programas usando `gdb`

Podemos examinar um programa durante sua execução usando o *gdb*. Podemos parar em qualquer instrução do programa, examinar conteúdo de registradores e da memória e listar todos os símbolos disponíveis (que podem ser funções ou variáveis globais).

!!! example
    Para compilar um programa com suporte a *debugging* usamos a flag `-g` do `gcc`



<div class="termy">

```console
$ gcc -g -Wall -pedantic parte1.c -o parte1
```

</div>


Siga os passos abaixo para para carregar um programa usando o *gdb*.

1. Lance o `gdb` e passe para ele seu programa:

<div class="termy">

```console
$ gdb ./parte1
```

</div>

2. Isto nos colocará em um prompt esperando comandos. Para rodar o programa até o fim execute

<div class="termy">

```console
(gdb) run
```

</div>

3. Para sair,

<div class="termy">

```console
(gdb) quit
```

</div>

!!! tip
    O *gdb* é uma ferramenta poderosa que possui muitas opções. Sua documentação está online e pode ser vista em [https://sourceware.org/gdb/current/onlinedocs/gdb/index.html#Top](https://sourceware.org/gdb/current/onlinedocs/gdb/index.html#Top).

Nesta primeira parte iremos abrir o arquivo *parte2.c* e olhar seu conteúdo. Também executaremos o programa compilado *parte2*.

!!! question
    Abra o código *parte2.c* e liste os nomes das variáveis globais declaradas e seus tamanhos. Anote também as funções declaradas.

!!! question
    O comando *info* mostra informações que podem ser obtidas a partir de um executável. Execute-o e veja o que acontece.

!!! example
    Use `info` para mostrar as funções e variáveis globais que existem em `parte2`.

!!! warning
    Muitos dos nomes são estranhos. Eles fazem parte do padrão de arquivos executáveis *ELF*, que contém informações específicas do sistema operacional usado. Você não precisa se preocupar com estes nomes.

!!! question
    Qual é o significado da primeira coluna do comando *info variables*?

    **Dica**: o valor está em hexadecimal, que usamos na expositiva para mostrar ponteiros.

!!! example
    Podemos usar o comando *print* para mostrar o valor inicial das variáveis globais identificadas. Mostre o valor inicial de `global_var` usando este comando e compare com o visto no arquivo *parte2.c*.

    **Dicas:**

    * Pode não funcionar de primeira. O quê a mensagem de erro diz?
    * A sintaxe de conversão de tipos de *C* (*casting*) pode ser útil aqui.


!!! example
    Podemos usar o *gdb* também para **examinar a memória** de um executável. Acesse esta [página da documentação](https://sourceware.org/gdb/current/onlinedocs/gdb/Memory.html), entenda como usar o comando `x` e escreva abaixo qual o comando usado para mostrar o conteúdo do segundo item do vetor `global_array`. Em seguida, teste-o e verifique que ele funcionou corretamente.


    **Dicas**:

    1. volte nos exercícios anteriores e encontre o endereço do início do vetor
    2. calcule o endereço do segundo elemento manualmente e passe para o comando `x`
    3. não se esqueça de buscar na memória o tamanho correto do elemento


!!! example
    `global_array` tem tipo `short`. Ou seja, é formado por dois bytes. Mostre agora o conteúdo de cada um deles. Ou seja, você deverá dar dois comandos para examinar a memória. Explique como converter esses dois bytes para o valor mostrado no exercício anterior.

!!! example
    Use agora o comando `x` para exibir `global_str` como uma *string*. Escreva o comando abaixo.

