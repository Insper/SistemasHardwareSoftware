# 10 - Revisão

Na aula de hoje iremos revisar nossas atividades com Assembly e representação de inteiros.

Quando tiver dúvidas, chamem os professores.

## Exercício 1

Abra o código-fonte ex1.c e confira a função main. Compile e execute o exercício 1 (ex1.c).

!!! question short
    O valor apresentado na saída confere com o presente no código? Por que isto acontece?

    !!! details "Resposta"
        O valor -1 em complemento de 2 é representado como uma sequência de 1's. Ao ser atribuído em uma unsigned short, teremos dezesseis 1's, mas que serão interpretados como unsigned. Somando $2^0 + 2^1 + \dots + 2^{15} = 65535$

!!! question short
    Qual o maior valor que pode ser armazenado em uma variável **unsigned short**?

!!! question short
    O que acontece quando tentamos armazenar um valor maior que o suportado pelo tipo de dados? Ex: atribuir 80000 para uma **unsigned short**.

## Exercício 2

Neste exercício iremos fazer engenharia reversa de Assembly para C. Os códigos-fonte estão disponíveis no repositório, mas evite abri-los antes de ter feito pelo menos uma primeira versão da engenharia reversa.

Compile o ex2.c com `gcc -Wall -std=c99 -Og ex2.c -c -o ex2` mas sem abrir o código-fonte e responda:

!!! question short
    Liste as variáveis e funções existentes.

Analise a função `func1` com o gdb e responda:

!!! question short
    Com base nos registradores utilizados, escreva a assinatura da função `func1`.

!!! question long
    Em `movw   $0x0,(%rdi)`, qual a operação realizada e o que significa o trecho `(%rdi)`?
    
!!! tip
    Veja a seção **Acesso a elementos constantes** da aula **09 - Arrays**

!!! question short
    Em `movw   $0x14,0x4(%rdi)`, qual a operação realizada e o que significa o trecho `0x4(%rdi)`?

!!! tip
    Acese na aula 05-Condicionais a explicação sobre as variântes da instrução `mov`

!!! question long
    Faça uma versão legível em *C* da função `func1`.

Analise a função `func2` com o gdb e responda:

!!! question short
    Com base nos registradores utilizados, escreva a assinatura da função `func2`.

!!! question short
    Qual a operação realizada em `lea    (%rax,%rax,4),%edx` na função `func2`?

!!! question short
    Qual a operação realizada em `add    %edx,%edx` na função `func2`?

!!! question short
    Você conseguiria agregar as operações `lea    (%rax,%rax,4),%edx` e `add    %edx,%edx` em uma única operação aritmética mais simples?

    !!! details "Resposta"
        Supondo que `%eax` representa a variável `i`, então a junção das duas operações é equivalente a fazer `i * 10`, cujo resultado é armazenado em `%edx`.


!!! question long
    Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

## Exercício 3

Neste exercício iremos fazer engenharia reversa de Assembly para C. Os códigos-fonte estão disponíveis no repositório, mas evite abri-los antes de ter feito pelo menos uma primeira versão da engenharia reversa.

Compile o ex3.c com `gcc -Wall -std=c99 -Og ex3.c -o ex3` mas sem abrir o código-fonte e responda:

!!! question short
    Liste as funções disponíveis.

!!! question short
    Faça a tradução das funções `func1` e `func2`. Existe alguma semelhança?

!!! tip
    Fique atento a chamadas de variáveis globais. Utilize o comando `x` para imprimir o conteúdo:
    ex:
    `x/d ` 0x100
    `x/s ` 0x100

!!! question short
    Defina a assinatura da função `func3` e faça sua tradução para C.

!!! question short
Defina a assinatura da função `func4`. Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

## Exercício 4

Neste exercício iremos fazer engenharia reversa de Assembly para C. Os códigos-fonte estão disponíveis no repositório, mas evite abri-los antes de ter feito pelo menos uma primeira versão da engenharia reversa.

Compile o ex3.c com `gcc -Wall -std=c99 -fno-stack-protector -Og ex4.c -o ex4` mas sem abrir o código-fonte e responda:

!!! question short
Defina a assinatura da função `ex4`. Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

!!! tip
    Fique atentos a chamadas de variáveis (relativos a `%rip`) e acessos à stack (relativos a `%rsp`).