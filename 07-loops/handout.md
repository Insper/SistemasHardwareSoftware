% 07 - Loops `while` e `for`
% Sistemas Hardware-Software - 2019/1
% Igor Montagner

# Parte 1 - loops `while` e `for`

**Exercício 1**: veja o código assembly abaixo e responda os itens.

~~~{asm}
0000 <soma_2n>:
0:   b8 01 00 00 00          mov    $0x1,%eax
5:   eb 05                   jmp    c <soma_2n+0xc>
7:   d1 ef                   shr    %edi
9:   83 c0 01                add    $0x1,%eax
c:   83 ff 01                cmp    $0x1,%edi
f:   77 f6                   ja     7 <soma_2n+0x7>
11:  f3 c3                   repz retq
~~~

1. Localize no código acima as instruções de saltos (`jmp` ou condicionais `j*`). Desenhe setas indicando para qual linha do código elas pulam. 

2. Analise o fluxo de saltos do seu código. Existe um loop? Entre quais linhas? \vspace{5em}
1. Comece fazendo uma versão *C* usando somente `if-goto` \vspace{15em}
1. Transforme a construção que você fez acima em um código usando `while`. \vspace{15em}

\pagebreak

Vamos agora exercitar o que vimos na aula expositiva. 

**Exercício 2**: Leia o código assembly abaixo e responda.

~~~{asm}
0000 <soma_n>:
0:   ba 00 00 00 00          mov    $0x0,%edx
5:   b8 00 00 00 00          mov    $0x0,%eax
a:   eb 09                   jmp    15 <soma_n+0x15>
c:   48 63 ca                movslq %edx,%rcx
f:   48 01 c8                add    %rcx,%rax
12:  83 c2 01                add    $0x1,%edx
15:  39 fa                   cmp    %edi,%edx
17:  7c f3                   jl     c <soma_n+0xc>
19:  f3 c3                   repz retq
~~~

1. Desenhe as flechas indicando o destino de cada instrução de pulo (`jmp` ou `j*`).
1. Escreva abaixo o cabeçalho da função `soma_n`. **Dica**: procure por registradores que são lidos *antes* de serem escritos. \vspace{3em} 
1. Faça a tradução do código acima para *C* usando somente `if-goto`\vspace{13em}
1. Converta o código acima para uma versão legível em *C*. \vspace{10em}

\newpage

<!--

**Desafio**: O exercício abaixo é bom para estudar para a prova/quiz! Ele é mais avançado, mas exercita todos os conceitos que vimos até agora.

~~~
0000 <min>:
0:    b8 00 00 00 00          mov    $0x0,%eax
5:    b9 00 00 00 00          mov    $0x0,%ecx
a:    eb 04                   jmp    10 <min+0x10>
c:    48 83 c0 01             add    $0x1,%rax
10:   48 63 d6                movslq %esi,%rdx
13:   48 39 c2                cmp    %rax,%rdx
16:   7e 0f                   jle    27 <min+0x27>
18:   48 8b 14 c7             mov    (%rdi,%rax,8),%rdx
1c:   48 39 14 cf             cmp    %rdx,(%rdi,%rcx,8)
20:   7e ea                   jle    c <min+0xc>
22:   48 89 c1                mov    %rax,%rcx
25:   eb e5                   jmp    c <min+0xc>
27:   48 8b 04 cf             mov    (%rdi,%rcx,8),%rax
2b:   c3                      retq
~~~

1. Desenhe as setas de pulos no código. 
1. Identifique quais jumps pertencem a um loop e quais pertencem a um `if`.
1. Escreva o cabeçalho da função. **Dica**: `%rdi` é usado na notação de acesso à memória com tamanho 8 (`long`). \vspace{3em}
\pagebreak

4. Faça uma versão `if-goto` deste código. \vspace{13em} 
1. Escreva ao lado de sua versão `if-goto` uma versão legível do código usando `if` e `while/for`.
-->

\pagebreak

# Parte 2 - variáveis locais

Como visto na expositiva, variáveis locais são armazenadas na pilha. O topo da pilha é armazenado em `%rsp` e ela cresce para baixo, ou seja, ao empilhar um dado o valor de `%rsp` diminui e ao desempilhar seu valor aumenta.

O compilador faz todo o possível para usar somente os registradores, porém em alguns casos é necessário guardar a variável na memória. Isso ocorre, em geral, quando usamos `&` para computar o endereço de uma variável.  

Funções que guardam variáveis na pilha seguem um padrão facilmente identificável. Primeiro elas subtraem um valor da pilha (`0x10` no exemplo abaixo) correspondente ao tamanho total de todas as variáveis usadas. Depois temos várias instruções usando endereços relativos a `%rsp` e por fim devolvemos o espaço usado somando `0x10` de volta a `%rsp`.

~~~{asm}
sub $0x10, %rsp
. . . // código da função aqui!
mov    0x8(%rsp),%eax
mov    %eax,%edx
add    0xc(%rsp),%edx
. . . // função continua 
add $0x10, %rsp
ret
~~~

**Exercício 1**: Um dos casos de uso mais comuns de variáveis na pilha é a criação de variáveis passadas para `scanf`. Note que isto vale para qualquer função que retorne um valor em um ponteiro. Vamos trabalhar na análise do executável `ex1scan`. (código assembly da função `main` abaixo)

~~~{asm}
06aa <main>:
   0x1149 <+0>:     sub    $0x18,%rsp
   0x114d <+4>:     lea    0xc(%rsp),%rsi
   0x1152 <+9>:     lea    0xeab(%rip),%rdi        # 0x2004
   0x1159 <+16>:    mov    $0x0,%eax
   0x115e <+21>:    callq  0x1040 <__isoc99_scanf@plt>
   0x1163 <+26>:    cmpl   $0x0,0xc(%rsp)
   0x1168 <+31>:    js     0x1180 <main+55>
   0x116a <+33>:    lea    0xe9f(%rip),%rdi        # 0x2010
   0x1171 <+40>:    callq  0x1030 <puts@plt>
   0x1176 <+45>:    mov    $0x0,%eax
   0x117b <+50>:    add    $0x18,%rsp
   0x117f <+54>:    retq   
   0x1180 <+55>:    lea    0xe80(%rip),%rdi        # 0x2007
   0x1187 <+62>:    callq  0x1030 <puts@plt>
   0x118c <+67>:    jmp    0x1176 <main+45>

~~~

1. Quanto espaço é reservado para variáveis locais? \vspace{3em}
1. Esse código chama funções três vezes. Você consegue reconhecê-las a partir dos nomes ao lado do `call`?\vspace{3em}
1. Nos três calls as funções recebem um endereço como primeiro argumento (`%rdi`). Use o *gdb* determinar o conteúdo destes endereços. Coloque o comando usado e conteúdo dos endereços abaixo. \vspace{5em}
1. Com base nas respostas acima, anote ao lado do assembly acima o código *C* equivalente à chamada `call`. \newpage
1. O código acima tem somente uma variável local. Identifique seu endereço e tamanho. (**Dica**: procure por endereços relativos a `%rsp`). \vspace{6em}
1. Finalmente, faça uma versão em *C* do código acima. Se necessário faça uma versão intermediária usando `if-goto`. 

# Extra - loops


**Extra 1**: A construção `do-while` é usada quando desejamos que o loop execute ao menos uma vez. Escreva uma versão `do-while` usando somente `if-goto` e labels. \vspace{10em}

**Extra 2**: Por vezes o `while` é traduzido pelo compilador usando a construção `do-while`. Adapte sua versão `if-goto` do `do-while` para ter o mesmo comportamento que o loop `while`. \vspace{10em}
