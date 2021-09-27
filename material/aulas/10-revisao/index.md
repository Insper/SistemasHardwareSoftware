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

Compile o ex2.c mas sem abrir o código-fonte e responda:

!!! question short
    Liste as variáveis e funções existentes.

Analise a função `func1` com o gdb e responda:

!!! question short
    Com base nos registradores utilizados, escreva a assinatura da função `func1`.

!!! question long
    Em `movw   $0x0,(%rdi)`, qual a operação realizada e o que significa o trecho `(%rdi)`?
    
        !!! details "Dica"
            Para este e o próximo exercício, veja a seção **Acesso a elementos constantes** da aula **09 - Arrays**

!!! question short
    Em `movw   $0x14,0x4(%rdi)`, qual a operação realizada e o que significa o trecho `0x4(%rdi)`?

!!! question long
    Faça uma versão legível em *C* da função `func1`.

Analise a função `func2` com o gdb e responda:

!!! question short
    Com base nos registradores utilizados, escreva a assinatura da função `func2`.

!!! question short
    Qual a operação realizada em `lea    (%rax,%rax,4),%edx` na função `func2`?

!!! question short
    Qual a operação realizada em `add    %edx,%edx` na função `func2`?

!!! question long
    Você conseguiria agregar as operações `lea    (%rax,%rax,4),%edx` e `add    %edx,%edx` em uma única operação aritmética mais simples?
    
        !!! details "Resposta"
        Suponto que em `%eax` temos a variável `i`, então estamos armazenando em `%edx` o equivalente a `i * 10`

!!! question long
    Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

