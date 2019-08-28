% 08 - Revisão de Assembly
% Sistemas Hardware-Software - 2019/2
% Igor Montagner

# Revisão de conceitos 

Nesta aula iremos rever alguns conceitos que podem ter passados despercebidos no meio de tanta informação que vimos nas últimas 4 aulas. 

## Ordem dos argumentos

As chamadas de função são feitas usando a seguinte ordem para os argumentos inteiros: `%rdi, %rsi, %rdx, %rcx, %r8, %r9`. **Esta ordem nunca muda**. Veja abaixo um exemplo de chamada de função.  

~~~{asm}
668:   41 b9 06 00 00 00       mov    $0x6,%r9d
66e:   41 b8 05 00 00 00       mov    $0x5,%r8d
674:   b9 04 00 00 00          mov    $0x4,%ecx
679:   ba 03 00 00 00          mov    $0x3,%edx
67e:   be 02 00 00 00          mov    $0x2,%esi
683:   bf 01 00 00 00          mov    $0x1,%edi
688:   e8 bd ff ff ff          callq  64a <exemplo1>
~~~

1. Traduza esta invocação de função para *C*: \vspace{10em}

## A instrução LEA

Se usada de maneira literal, a instrução LEA (**L**oad **E**ffective **A**ddress) serve para calcular o endereço de uma variável local e é equivalente ao operador `&` em *C*. Porém, ela é frequentemente "abusada" para fazer aritmética. Um ponto importante quando usamos `LEA` é que todos os operandos são registradores de `64` bits.

Veja um exemplo abaixo.

~~~{.asm}
00000000000005fa <func>:
5fa:   48 8d 44 7f 02          lea    0x2(%rdi,%rdi,2),%rax
5ff:   c3                      retq

0000000000000600 <main>:
600:   bf 03 00 00 00          mov    $0x3,%edi
605:   e8 f0 ff ff ff          callq  5fa <func>
60a:   f3 c3                   repz retq
~~~

1. Qual é o resultado da chamada de `func(3)` pelo `main`? \vspace{5em}

2. Escreva abaixo a fórmula usada pelo `LEA` para o cálculo do valor acima.\vspace{5em}

A melhor maneira de identificar qual tipo de uso estamos fazendo é observar os operandos usados no `LEA` e o uso feito de seu resultado. Por isso é  muito importante identificar os parâmetros das funções. Se os operandos representarem parâmetros inteiros (`int` ou `long`) então certamente será um caso de aritmética. Se eles forem ponteiros então se trata do operador `&`.

Em nossos exemplos, `LEA` aparece sempre com o registrador `%rsp` para calcularmos endereços de variáveis na pilha. Logo, a ocorrência de `LEA` com `%rsp` certamente é um caso em que usamos `&`. Além disto, se usamos `LEA` para preencher um registrador usado em um `call` então esse registrador provavelmente representa um argumento ponteiro. 

Veja um outro exemplo abaixo:

~~~{.asm}
0000000000000000 <func2>:
0:   48 8d 04 7f             lea    (%rdi,%rdi,2),%rax
4:   48 8d 44 b0 ec          lea    -0x14(%rax,%rsi,4),%rax
9:   c3                      retq
~~~

1. Faça a declaração da função acima. \vspace{5em}

2. Para cada instrução `LEA` em `func2`, escreva a expressão computada. \vspace{7em}

3. Escreva uma expressão legível em *C* que faça o mesmo cálculo que os `LEA` acima. \vspace{5em}

## Inicialização de variáveis do tipo `long`

O compilador faz o possível para gerar executáveis pequenos. Isto é vantajoso tanto para o espaço em disco como para o desempenho quando executamos o programa, já que um programa com menos bytes é carregado mais rapidamente da memória.

Um efeito colateral disto é que alguns códigos ficam menos legíveis para nós. Um ponto comum de confusão é a inicialização de registradores de `64`bits (como `%rax` e `%rdi`) usando instruções de `32` bits (como `%eax` e `%rdi`). Nestes casos, devemos identificar o tipo da variável pelas operações aritméticas seguintes. 

Por exemplo, se um registrador é inicializado usando `mov $0, %edx` mas depois fazemos a operação `add $1, %rdx`, então ele representa uma variável do tipo `long`. Se a operação aritmética fosse `add $1, %edx` então seria um tipo `int`. 

Leia o código abaixo e responda.

~~~{asm}

00000000000005fa <prod>:
5fa:   ba 01 00 00 00          mov    $0x1,%edx
5ff:   b8 01 00 00 00          mov    $0x1,%eax
604:   eb 08                   jmp    60e <prod+0x14>
606:   48 0f af c2             imul   %rdx,%rax
60a:   48 83 c2 01             add    $0x1,%rdx
60e:   48 39 fa                cmp    %rdi,%rdx
611:   7c f3                   jl     606 <prod+0xc>
613:   f3 c3                   repz retq

0000000000000615 <main>:
615:   bf 64 00 00 00          mov    $0x64,%edi
61a:   e8 db ff ff ff          callq  5fa <prod>
~~~

1. Só pela chamada de `prod` não conseguimos dizer se o tipo do argumento é `int` ou `long`. Onde, em `prod`, encontramos informações suficientes para determinar isto? \vspace{5em}

2. Os registradores `%edx` e `%eax` são inicializados logo no começo da função e representam variáveis locais em `prod`. Quais os tipos dessas variáveis? \vspace{5em}

3. Faça a tradução desta função para *C* usando `if-goto` \vspace{15em}

4. Transforme seu código acima em uma versão legível. \vspace{15em}

\newpage

Vamos agora compreender um executável do começo ao fim tanto olhando seu Assembly como acompanhando sua execução via *gdb*.


**Exercício**: Abra o executável **extra1** no *gdb*.

1. Quais funções estão definidas (além do `main`)? Declare-as no espaço abaixo. \vspace{5em}
1. O `main` chama as funções acima? Em qual endereço? \vspace{5em}
1. Estas funções chamam outras funções? Se sim, qual chama qual e em qual endereço? \vspace{5em}
1. Pare a execução do programa logo antes da chamada de `funcao1` no `main`. Quais são os argumentos passados para ela? \vspace{5em}
1. Olhe agora o disassembly de `funcao1`. Escreva abaixo uma versão em *C* desse código. \vspace{20em}
1. Ainda não é possível saber o que faz `funcao2`, mas podemos simular isso. Coloque um *breakpoint* antes e um após a chamada de `funcao2`. Você consegue  identificar o quê mudou? Onde você procuraria isso? \vspace{10em} 
1. Sabendo o que `funcao2` faz via observação de suas entradas e saídas, faça sua tradução para *C*.  \vspace{10em}