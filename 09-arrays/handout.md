% 08 - Ponteiros e Arrays
% Sistemas Hardware-Software - 2019/2
% Igor Montagner


# Ponteiros (de novo)

Retornar valores usando ponteiros é muito comum em programação de sistemas, especialmente em funções de interface com o sistema operacional. Um padrão muito comum é a função retornar um inteiro que representa um código de erro (`0` se foi tudo bem, qualquer outra coisa se houve problema) e preencher o resultado da função em uma variável passada como ponteiro. Veja o exemplo de uso abaixo.

~~~{.c}
int divide_se_der(int a, int b, int *res) {
    if (b == 0) return -1;
    *res = a/b;
    return 0;
}
int main() {
    int a, b, res;
    scanf("%d %d", &a, &b);
    if (divide_se_der(a, b, &res)) {
        printf("Divisão por 0 não é válida!\n");
    } 
    printf("%d / %d = %d\n", a, b, res);
}
~~~


O código Assembly da função `divide_se_der` está copiado abaixo. Um indício muito forte que uma função retorna algo em um parâmetro é um `mov` do tipo que ocorre na linha `0xc` logo antes do `retq`. Este `mov` copia o valor de `%eax` (resultado da divisão) para o valor apontado pelo terceiro argumento (`(%rcx)`). Logo, ele retorna um valor via um ponteiro.

~~~
0000000000000000 <divide_se_der>:
0:   89 f8                   mov    %edi,%eax
2:   48 89 d1                mov    %rdx,%rcx
5:   85 f6                   test   %esi,%esi
7:   74 0b                   je     14 <divide_se_der+0x14>
9:   99                      cltd
a:   f7 fe                   idiv   %esi
c:   89 01                   mov    %eax,(%rcx)
e:   b8 00 00 00 00          mov    $0x0,%eax
13:  c3                      retq
14:  b8 ff ff ff ff          mov    $0xffffffff,%eax
19:  c3                      retq
~~~

\newpage

Vamos agora exercitar. Analise o código assembly abaixo. Para revisar também o `LEA`, o exercício abaixo mistura ponteiros e contas usando `LEA`.

~~~{asm}
000000000000066a <func5>:
66a:   85 ff                   test   %edi,%edi
66c:   7e 0d                   jle    67b <func5+0x11>
66e:   8d 04 7e                lea    (%rsi,%rdi,2),%eax
671:   89 02                   mov    %eax,(%rdx)
673:   8d 04 76                lea    (%rsi,%rsi,2),%eax
676:   01 c7                   add    %eax,%edi
678:   89 39                   mov    %edi,(%rcx)
67a:   c3                      retq
67b:   8d 04 37                lea    (%rdi,%rsi,1),%eax
67e:   89 02                   mov    %eax,(%rdx)
680:   29 f7                   sub    %esi,%edi
682:   89 39                   mov    %edi,(%rcx)
684:   c3                      retq
~~~

A função `func5` é chamada pelo trecho de código abaixo:

~~~{asm}
699:   48 8d 4c 24 0c          lea    0xc(%rsp),%rcx
69e:   48 8d 54 24 08          lea    0x8(%rsp),%rdx
6a3:   be 04 00 00 00          mov    $0x4,%esi
6a8:   bf 01 00 00 00          mov    $0x1,%edi
6ad:   e8 b8 ff ff ff          callq  66a <func5>
~~~

1. Quais são os tipos parâmetros da função acima? Lembre-se das regras de identificação de uso da instrução `LEA` que vimos na revisão. \vspace{5em} 

2. Podemos saber, pelos acessos à memória feitos em `func5`, para qual tipo de dados os argumentos que são ponteiros apontam. Em quais linhas isto pode ser visto? Quais são os tipos de dados dos ponteiros? \vspace{15em}

3. Faça uma versão *C* usando `if-goto` \vspace{15em}

4. Transforme seu código acima em uma versão legível de *C* \vspace{15em}

# Arrays

Os exercícios abaixo trabalham com arrays. Já sabemos todo o necessário para lidar com eles: a notação de cálculos de endereços de memória é usada para encontrar o endereço de cada elemento do vetor. Vejamos novamente a notação de cálculo de endereços de memória: `D(%reg1, %reg2, S)`, onde 

* `D` é um número inteiro que representa um deslocamento constante a partir do endereço guardado em `%reg1`
* `%reg1` contém o endereço do primeiro elemento do vetor
* `%reg2` contém o índice do elemento a ser acessado
* `S` contém o tamanho de cada elemento do vetor e pode ser `1, 2, 4` ou `8`.

O acesso é feito ao endereço `D + %reg1 + S * %reg2`. Em *C*, acessos a vetor do tipo `vec[i]` (supondo `int *vec`) são traduzidos para `(%reg1, %reg2, 4)`,  onde `%reg1 = &vec[0]` e `%reg = (long) i`. 

**Exercício:** Considerando um vetor `short *vec` e que o endereço do primeiro elemento de `vec` esteja em `%rdi`

1. qual a instrução usada para mover o conteúdo de `vec[i]` para o registrador `%eax` ?(supondo que o valor de `i` esteja em `%esi`) \vspace{3em}
2. qual a instrução usada para mover `&v[i]` para o registrador `%eax`?

O acesso a elementos "constantes", como `long *v; v[5] = 0;`, não é feito usando a notação acima, pois o compilador já sabe **em tempo de compilação**, qual é o deslocamento necessário para encontrar a posição 6 de `v`.

**Exercício:** Considerando o exemplo acima, responda.

1. Supondo que `v=0x100`, qual o é o endereço de `v[5]`? \vspace{3em}
1. Escreva a instrução usada para mover o valor `0` para `v[5]` (supondo que o endereço do primeiro elemento esteja em `%rdi`). \vspace{3em}

-----

~~~{asm}
0000000000000000 <func_que_recebe_array>:
0:   8b 47 04                mov    0x4(%rdi),%eax
3:   03 07                   add    (%rdi),%eax
5:   3b 47 08                cmp    0x8(%rdi),%eax
8:   0f 9c c0                setl   %al
b:   0f b6 c0                movzbl %al,%eax
e:   c3                      retq
~~~

1. Temos acessos à memória relativos ao endereço passado em `%rdi` nas linhas `0, 3` e `5`. Isto significa que `%rdi` é um ponteiro. Pelos tipos de acessos feitos, você consegue identificar para qual tipo de dados ele aponta?\vspace{7em}
2. Traduza os acessos de memória feitos nas linhas citadas acima para a notação de acesso a arrays em *C*. \vspace{7em}
3. Com base no respondido acima, faça uma versão em *C* legível do código asembly acima. Se ajudar, faça uma tradução linha a linha do Assembly e depois torne-a legível. \vspace{15em}

**Exercício**: veja o código abaixo e responda as perguntas.

~~~{.asm}
0000000000000000 <soma>:
   0:   ba 00 00 00 00          mov    $0x0,%edx
   5:   b8 00 00 00 00          mov    $0x0,%eax
   a:   eb 09                   jmp    15 <soma+0x15>
   c:   48 63 ca                movslq %edx,%rcx
   f:   03 04 8f                add    (%rdi,%rcx,4),%eax
  12:   83 c2 01                add    $0x1,%edx
  15:   39 f2                   cmp    %esi,%edx
  17:   7c f3                   jl     c <soma+0xc>
  19:   f3 c3                   repz retq
~~~

1. A função acima usa vários registradores. Para facilitar a descoberta de quais são parâmetros da função anote abaixo cada registrador usado e, ao lado, a linha do primeiro uso e se esse uso foi leitura ou escrita. \vspace{9em}

2. Se o primeiro acesso a registrador é de escrita então ele provavelmente não é um parâmetro. Com base nisto, escreva abaixo a declaração da função acima. \vspace{9em}

3. Sempre que escrevemos a notação de acesso à memória `D(%reg1, %reg2, S)` precisamos usar registradores de `64` bits nos lugares de `reg1` e `reg2`. Com base nisto, explique qual o uso feito do registrador `%edx` e porquê usamos a instrução `movslq` na linha `c`. \vspace{9em}

4. Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.  \vspace{20em}


**Exercício**: Veja agora o código abaixo e responda. 

~~~{.asm}
0000000000000000 <first_neg>:
   0:   b8 00 00 00 00          mov    $0x0,%eax
   5:   39 f0                   cmp    %esi,%eax
   7:   7d 0e                   jge    17 <first_neg+0x17>
   9:   48 63 d0                movslq %eax,%rdx
   c:   83 3c 97 00             cmpl   $0x0,(%rdi,%rdx,4)
  10:   78 05                   js     17 <first_neg+0x17>
  12:   83 c0 01                add    $0x1,%eax
  15:   eb ee                   jmp    5 <first_neg+0x5>
  17:   f3 c3                   repz retq
~~~

1. A função acima usa vários registradores. Para facilitar a descoberta de quais são parâmetros da função anote abaixo cada registrador usado e, ao lado, a linha do primeiro uso e se esse uso foi leitura ou escrita. \vspace{9em}

2. Desenhe setas indicando o destino dos pulos no código acima. Você consegue idenfiticar quais estruturas de controle? Entre quais linhas? \vspace{9em}

3. Faça uma versão em *C* usando `if-goto` do código acima. \vspace{15em}

4. Transforme seu código em uma versão legível. \vspace{15em}


