---
title: "Introdução a Assembly I: funções"
author: "Igor Montagner"
...

\begin{center}
Data de entrega: 30/08
\end{center}

Neste handout vamos trabalhar pela primeira vez na tradução reversa de programas em Assembly para *C*. Nas últimas aulas vimos as instruções `mov` e `lea` e na aula de hoje vimos uma grande tabela com as instruções aritméticas (`add`, `sub`, `mul`, `imul`, `div`, etc). 

Como em todas as aulas, veremos hoje um detalhe a mais sobre arquitetura *x64*: chamadas de funções e argumentos.

------------

### Arquitetura de computadores II:

Em *x64* os argumentos das funções são passados nos registradores e o valor de retorno é colocado também em um registrador. 

1. **Argumentos inteiros ou ponteiros** são passados nos registradores `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8` e `%r9` (nesta ordem).
1. **Argumentos ponto flutuante** são passados nos registradores `%xmm0` até `%xmm7`.
1. **Valores de retorno inteiros ou ponteiros** são colocados no registrador `%rax`.
1. **Valores de retorno ponto flutuante** são colocados no registrador `%xmm0`. 

Para chamar funções usamos a instrução `call` seguido do endereço de memória da função. Tanto `objdump` quanto `gdb` criam um "apelido" para estes endereços de memória usando o nome original da função no arquivo *.c*. Assim, estas instruções são mostradas, normalmente, como `call func1`, por exemplo. Note que antes de cada `call` devemos preencher os argumentos nos registradores corretos. 

Para retornar usamos a instrução `ret`. Ela é equivalente ao comando `return` de *C* e devolverá o valor armazenado no `%rax` (ou `%xmm0` para ponto flutuante). 

![Registradores de 64 e 32 bits \label{reg64}](registradores-grandes.png){width=300px}

![Registradores de 32, 16 e 8 bits \label{reg-small}](registradores-pequenos.png){width=300px}


Não se esqueça da equivalência entre o tamanhos dos registradores e os tipos inteiros em *C*. Um resumo gráfico pode ser visto nas figuras \ref{reg64} e \ref{reg-small}.

1. 64 bits (`%rax`, `%rdi` e outros que começam com `r`): (`unsigned`) `long` ou ponteiro;
1. 32 bits (`%eax`, `%edi` e outros que começa com `e` e os que terminam em `d` como `r10d`): `int` ou `unsigned int`;
1. 16 bits (`%ax`, `%di` e outros com duas letras somente terminando em `x`): `short` ou `unsigned short`
1. 8 bits (`%al`, `%ah` e outros com duas letras terminando em `h` ou `l`): `char` ou `unsigned char`.

Vamos agora praticar fazendo a tradução de funções que fazem aritmética simples entre inteiros (usando ou não ponteiros). O exemplo abaixo mostra todas as etapas que precisamos seguir para fazer a tradução Assembly -> C.

**Exemplo**: dado o código Assembly abaixo, faça sua tradução para *C*

~~~{asm}
0000000000000000 <misterio1>:
0:   48 01 f7                add    %rsi,%rdi
3:   48 8d 04 57             lea    (%rdi,%rdx,2),%rax
7:   c3                      retq
~~~

#### Assinatura da função 

Vamos começar pela assinatura da função. O código assembly usa os registradores `%rdi`, `%rsi`, `%rdx` e `%rax`. Consultando o box de arquitetura de computadores, vemos que a função recebe três argumentos do tipo `long` (pois usa os registradores de 64 bits). Vemos também que o resultado das computações é guardado em `%rax`, logo o tipo de retorno também é `long`. A assinatura da função é, portanto

`long misterio1(long a, long b, long c);`

Note que o tipo dos argumentos poderia ser pointeiro também. Porém, olhando rapidamente o código notamos que não há nenhum acesso a memória. Logo, se trata realmente de `long`.

#### O código

Vamos agora para o código. Nossa primeira estratégia é atribuir um nome para cada registrador. Os três registradores de argumentos já receberam os nomes `a`, `b` e `c`. Para deixar explícito o papel do `%rax` vamos nomeá-lo de `retval`. 

A primeira instrução `add %rsi, %rdi` realiza a adição dos dois registradores e armazena em `%rdi`. Logo, sua tradução direta seria:

~~~{c}
a += b;
~~~

A instrução `lea (%rdi, %rdx, 2), %rax` é usada tanto para calcular endereços de memória quanto para aritmética simples. Vemos que é o segundo caso pois, no código seguinte, não acessamos a memória com o valor calculado. Logo, podemos traduzir este trecho como

~~~{c}
retval = a + 2 * c;
~~~

Logo após temos o `ret`, que é traduzido como

~~~{c}
return retval;
~~~

Logo, nossa função é traduzida como 

~~~{c}
long misterio1(long a, long b, long c){ 
    long retval;
    a += b;
    retval = a + 2*c;
    return retval;
}
~~~

Finalmente, podemos deixar nosso código legível e escrevê-lo como

~~~{c}
long misterio1(long a, long b, long c){ 
    return a + b + 2*c;
}
~~~

--------------------

O processo acima pode ser formalizado no seguinte algoritmo:

1. Identifique quantos argumentos a função recebe
1. Identifique os tipos de cada argumento (pode ser necessário olhar o código)
1. Dê um nome para cada registrador. Se um mesmo registrador é usado com tamanhos diferentes (`%rdi` e `%edi` são usados no código), dê um nome diferente para cada tamanho.
1. Faça a tradução de cada instrução separadamente.
1. Fique atento aos valores colocados em `%rax` e `%eax` perto do fim do código. Esses valores serão retornados pela função.
1. O código gerado está correto, mas costuma ser ilegível. Refatore-o para melhorar sua legibilidade. 


**Dicas**: 

* A instrução `lea` pode ser usada tanto para aritmética quanto para cálculo de endereços. Para tirar a dúvida basta olhar se as próximas instruções fazem acesso à memória com o endereço calculado ou apenas usam o valor diretamente (aritmética).
* Os registradores de tamanhos menores são virtuais. Quanto escrevo em `%ax` estou escrevendo nos 16 bits menos significativos de `%rax` e de `%eax` também. 
* Muitas instruções com operadores de 32bits zeram os 32bits superiores. Assim, vemos por exemplo a instrução `mov $0, %eax` sendo usada para zerar um `long`.

--------------------

\pagebreak

Vamos agora exercitar. Cada exercício faz um cálculo diferente. Se houver alguma instrução desconhecida, pesquise-a no google para encontrar seu significado. Normalmente algo como "asm x64 instruction" + a instrução desconhecida dá respostas corretas.

**Exercício 1**: O código abaixo foi retirado do arquivo `ex1.o`. Faça sua tradução para *C*.

~~~{asm}
0000000000000000 <ex1>:
0:   89 f8                   mov    %edi,%eax
2:   29 f0                   sub    %esi,%eax
4:   c3                      retq
~~~

Sua solução: \vspace{10em}

**Exercício 2**: Execute `objdump` no arquivo `ex2.o` e cole seu disassembly abaixo. \vspace{10em}


Faça a tradução desta função para *C*. \vspace{10em}


\pagebreak

**Exercício 3**: A função abaixo foi obtida de `ex3.o`.  

~~~{asm}
0000000000000000 <ex3>:
0:   8b 06                   mov    (%rsi),%eax
2:   0f af c0                imul   %eax,%eax
5:   89 07                   mov    %eax,(%rdi)
7:   c3                      retq
~~~

1. O quê faz a instrução `imul`? \vspace{5em}

1. Traduza esta função para *C*. Fique atento ao tamanho dos registradores usados para identificar o tamanho dos variáveis inteiras.  \vspace{10em}

Antes de prosseguir, valide suas soluções da seção anterior com o professor.

Vamos agora trabalhar com executáveis "completos". Vamos analisar não somente o código das funções mas também sua chamada.

**Exercício 4**: Neste exercício vamos analisar o executável `ex4`. Execute `objdump` neste arquivo e cole abaixo o conteúdo das funções `main` e `ex4`. \vspace{10em}


Localize a chamada da função `ex4` no main. Quantos argumentos a função recebe? Quais são seus valores?   \vspace{10em}

Traduza a função `ex4` para *C*. \vspace{10em} 

**Exercício 5**: Neste exercício vamos nos aprofundar no uso de ponteiros. Vimos no exercício 3 um exemplo de função que armazenava um valor calculado em um ponteiro. Agora veremos um exemplo completo que inclui a chamada de uma função recebendo um endereço.

O trecho abaixo copia os argumentos para os registradores corretos e chama a função.

~~~{asm}
60b:   48 8d 4c 24 08          lea    0x8(%rsp),%rcx
610:   48 8d 54 24 0c          lea    0xc(%rsp),%rdx
615:   be 03 00 00 00          mov    $0x3,%esi
61a:   bf 0a 00 00 00          mov    $0xa,%edi
61f:   e8 d6 ff ff ff          callq  5fa <ex5>
~~~

Identifique a partir dos tipos de dados colocados nos registradores qual o tipo dos argumentos da função. \vspace{5em}


Qual são os endereços passados para a função `ex5`? Eles são passados em quais registradores? \vspace{5em}

Vamos agora ao código de `ex5`:

~~~{asm}
00000000000005fa <ex5>:
5fa:   89 f8                   mov    %edi,%eax
5fc:   48 89 d7                mov    %rdx,%rdi
5ff:   99                      cltd
600:   f7 fe                   idiv   %esi
602:   89 07                   mov    %eax,(%rdi)
604:   89 11                   mov    %edx,(%rcx)
606:   c3                      retq
~~~

1. Como a instrução `idiv` funciona? Em quais registradores ela posiciona seu resultado? Em quais registradores ela espera a entrada? \vspace{7em}
1. O quê faz a instrução `cltd`? Por quê ela é necessária? \vspace{5em}
1. Faça a tradução de `ex5` para *C*.

