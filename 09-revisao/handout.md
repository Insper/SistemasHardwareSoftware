% 09 - Prática de Engenharia Reversa
% Sistemas Hardware-Software - 2020/1
% Igor Montagner 

As aulas de hoje e quinta serão dedicadas a revisar conceitos básicos vistos nas últimas 5 aulas. A parte 1 repassa chamadas de funções e o uso da instrução `LEA`. A parte 2 contém exercícios intermediários que misturam dois conceitos vistos em aula (ex: loops e `LEA` ou funções + condicionais). Está indicado ao lado de cada exercício quais conceitos são exercitados e todos eles serão recebidos via repositório de atividades da disciplina. 

**Atenção**: acesse a aba "Repositório de Atividades" no Teams para indicar seu usuário do blackboard e endereço do repositório privado no Github.  

Todo exercício para entrega deverá ser colocado no repositório de atividades da disciplina.

# Parte 1 - Revisão de funções e `LEA`

Todos os exercícios da revisão serão feitos com o arquivo `exemplo1` (compilado a partir de `exemplo1.c`).

## Chamadas de funções

As chamadas de função são feitas usando a seguinte ordem para os argumentos inteiros: 

1. `%rdi`
2. `%rsi`
3. `%rdx`
4. `%rcx`
5. `%r8`
6. `%r9` 

**Esta ordem nunca muda**. Veja abaixo um exemplo de chamada de função.  

~~~{asm}
   0x065c <+4>:	    mov    $0x6,%r9d
   0x0662 <+10>:	mov    $0x5,%r8d
   0x0668 <+16>:	mov    $0x4,%ecx
   0x066d <+21>:	mov    $0x3,%edx
   0x0672 <+26>:	mov    $0x2,%esi
   0x0677 <+31>:	mov    $0x1,%edi
   0x067c <+36>:	callq  0x64a <exemplo1>
   0x0681 <+41>:	lea    0xa(%rax),%esi
~~~

**Exercício**: Traduza esta invocação de função para *C*: 

\newpage 

Vamos agora analisar o código de `exemplo1`:

```asm
Dump of assembler code for function exemplo1:
   0x064a <+0>:	    add    %esi,%edi
   0x064c <+2>:	    add    %edi,%edx
   0x064e <+4>:	    add    %edx,%ecx
   0x0650 <+6>:	    add    %r8d,%ecx
   0x0653 <+9>:	    lea    (%rcx,%r9,1),%eax
   0x0657 <+13>:	retq
```

Vemos na linha `exemplo1+9` que colocamos um valor no registrador `%eax` e depois finalizamos a função usando `retq`. Este é o segundo ponto que nunca muda: **o valor de retorno de toda função é colocado no registrador `%rax`** (ou uma de suas partes menores). A instrução usada é o `LEA` que veremos na seção a seguir.

## Operações aritméticas usando `LEA`

Se usada de maneira literal, a instrução LEA (**L**oad **E**ffective **A**ddress) serve para calcular o endereço de uma variável local e é equivalente ao operador `&` em *C*. Porém, ela é frequentemente "abusada" para fazer aritmética. Um ponto importante quando usamos `LEA` é que todos os operandos são registradores de `64` bits.

**Regra geral**: 

1. Se `LEA` for usada com o registrador `%rsp` então ela sempre representa o operador `&`
1. Se os registradores envolvidos foram usados como números inteiros em instruções anteriores, então ela representa uma conta com os valores dos registradores.

Vejamos o exemplo da função `exemplo1` acima:

```asm
   0x0653 <+9>:	    lea    (%rcx,%r9,1),%eax
```

No exemplo acima `LEA` é usada para fazer aritmética. Sabemos disso pois, na chamada traduzida na parte anterior, elas recebem números inteiros (`%r9d = 6` e `%ecx = 4`). Seu primeiro argumento segue a seguinte lógica

```asm
C(%R1, %R2, S)
``` 

* `C` é uma constante
* `%R1` é um registrador
* `%R2` é um registrador (pode ser igual a `%R1`)
* `S` é `1, 2, 4`  ou `8` (todos os tamanhos possíveis de registradores inteiros)

A operação acima calcula `C + %R1 + (%R2 * S)`. A operação `LEA` **nunca acessa a memória**, apenas move o resultado deste cálculo para o registrador destino. **Qualquer outra operação que use a sintaxa acima está fazendo um acesso a memória. `LEA` é a única exceção!**

**Exercício**: traduza a operação abaixo para *C*

```asm
   0x0653 <+9>:	    lea    (%rcx,%r9,1),%eax
```

\newpage

**Exercício**: Com estas informações em mãos, traduza `exemplo1` para *C*

```asm
Dump of assembler code for function exemplo1:
   0x064a <+0>:	    add    %esi,%edi
   0x064c <+2>:	    add    %edi,%edx
   0x064e <+4>:	    add    %edx,%ecx
   0x0650 <+6>:	    add    %r8d,%ecx
   0x0653 <+9>:	    lea    (%rcx,%r9,1),%eax
   0x0657 <+13>:	retq
```

\vspace{10em}

## Retorno de funções

Vamos terminar nossa revisão analisando novamente a chamada de `exemplo1` no `main`:

```asm
   0x065c <+4>:	    mov    $0x6,%r9d
   0x0662 <+10>:	mov    $0x5,%r8d
   0x0668 <+16>:	mov    $0x4,%ecx
   0x066d <+21>:	mov    $0x3,%edx
   0x0672 <+26>:	mov    $0x2,%esi
   0x0677 <+31>:	mov    $0x1,%edi
   0x067c <+36>:	callq  0x64a <exemplo1>
   0x0681 <+41>:	lea    0xa(%rax),%esi
```

Anteriormente já vimos que o `call` e os `mov` s acima fazem a chamada `exemplo1(1,2,3,4,5,6)` em *C*. 
A linha de baixo realiza uma operação aritmética com `%rax`. 

**Exercício**: considerando que `%rax` armazena o valor de retorno de uma função, qual seria a tradução para *C* do bloco de código acima? \vspace{5em}



# Parte 2 - exercícios intermediários

Os exercícios desta seção exercitam dois conceitos ao mesmo tempo. Cada um deles é disponibilizado via um arquivo `exI.o` na pasta `09-revisao` no repositório de atividades. A soluções devem ser colocadas no arquivo `solucao_exI.c` correspondente. Veja as instruções em cada arquivo para garantir que está implementando a função correta.

**Importante**: cada exercício estará disponível em uma página do handout de revisão juntamente com questões "padrão" para cada assunto. Essas questões são feitas para ajudar na compreensão dos programas. Faça-as com atenção e facilite sua vida. 

\newpage

**Exercício**: As função abaixo exercita os assuntos **Aritmética** e **Expressões booleanas**. 
 
```asm
Dump of assembler code for function ex1:
   0x05fa <+0>:	    lea    (%rdi,%rsi,1),%rax
   0x05fe <+4>:	    lea    (%rax,%rdx,4),%rcx
   0x0602 <+8>:	    imul   %rdi,%rdi
   0x0606 <+12>:	lea    (%rdi,%rsi,2),%rax
   0x060a <+16>:	add    %rax,%rdx
   0x060d <+19>:	cmp    %rdx,%rcx
   0x0610 <+22>:	setge  %al
   0x0613 <+25>:	movzbl %al,%eax
   0x0616 <+28>:	retq   
```

1. Quantos argumentos a função acima recebe? Quais seus tipos? Declare a função abaixo. \vspace{5em}

1. As instruções `LEA` acima representam operações aritméticas ou a operação *endereço de* `&`? Como você fez esta identificação? \vspace{5em}.

1. Traduza as operações das linhas `ex1+0` até `ex1+15` para *C* \vspace{10em}

1. Nas linhas `ex1+18` e `ex1+21` é feita uma comparação. Qual e entre quais registradores? Onde é armazenado este resultado? \vspace{5em}

1. O quê faz a instrução `movzbl` em `ex1+24`? Juntando com a resposta da pergunta acima, traduza as instruções `ex1+18` até `ex1+27` para *C*.\vspace{5em}

Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes. 

\newpage

**Exercício**: O exercício abaixo exercita **Chamadas de funções** e **Condicionais**. 

```asm
Dump of assembler code for function ex2:
   0x05ff <+0>:	    push   %rbx
   0x0600 <+1>:	    mov    %rdi,%rbx
   0x0603 <+4>:	    mov    %rsi,%rdi
   0x0606 <+7>:	    callq  0x5fa <vezes2>
   0x060b <+12>:	cmp    %rbx,%rax
   0x060e <+15>:	jle    0x613 <ex2+20>
   0x0610 <+17>:	add    %rbx,%rbx
   0x0613 <+20>:	add    %rbx,%rax
   0x0616 <+23>:	pop    %rbx
   0x0617 <+24>:	retq   
```

1. Quantos argumentos a função acima recebe? Quais são seus tipos? Declare-a abaixo. \vspace{5em}

Vamos começar trabalhando na linha `ex2+7`, na instrução `call vezes2` . A chamada necessita usar o registrador `%rdi`, mas ele contém o primeiro argumento de `ex2`. 

1. Em qual registrador é guardado o primeiro argumento de `ex2`? Isso é feito antes da chamada `call`. \vspace{5em}

1. Qual variável é passada como argumento para a função `vezes2` ? \vspace{5em}

1. Escreva abaixo a invocação de `vezes2`. \vspace{5em}


Você deve ter notado as instruções `push/pop %rbx` no começo/fim da função. Toda função pode usar os registradores de argumentos (vistos na parte 1) e o de valor de retorno como quiserem. Se precisarem mexer nos outros registradores a prática é salvá-los na pilha no começo da função e restaurá-los no fim. Assim não importa o que a função faça, para a função chamadora é como se não houvesse havido nenhuma modificação nos outros registradores.  \newpage

Vamos agora olhar a condicional na linha `ex2+12`.

1. Após a chamada `call`, qual o conteúdo de `%rax`? \vspace{5em}

1. Juntando suas respostas nas questões de cima, qual é a comparação feita nas linhas `ex2+12, ex2+17` ? \vspace{5em}

1. Com essas informações em mãos, faça uma tradução do código acima para *C* usando somente `if+goto`. \vspace{10em}


Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes. 

\newpage

**Exercício**: O exercício abaixo exercita **Ponteiros** e **Expressões booleanas**. 

```asm
Dump of assembler code for function ex3:
   0x05fa <+0>:	    cmp    %rsi,%rdi
   0x05fd <+3>:	    setl   %al
   0x0600 <+6>: 	movzbl %al,%eax
   0x0603 <+9>:	    mov    %eax,(%rdx)
   0x0605 <+11>:	cmp    %rsi,%rdi
   0x0608 <+14>:	sete   %al
   0x060b <+17>:	movzbl %al,%eax
   0x060e <+20>:	mov    %eax,(%rcx)
   0x0610 <+22>:	cmp    %rsi,%rdi
   0x0613 <+25>:	setg   %al
   0x0616 <+28>:	movzbl %al,%eax
   0x0619 <+31>:	mov    %eax,(%r8)
   0x061c <+34>:	retq   
```

1. Quantos argumentos a função acima recebe? De quais tipos? Declare-a abaixo. \vspace{5em}

1. A função acima faz várias comparações. Liste quais e entre quais argumentos. \vspace{7em}

1. Onde é armazenado o resultado de cada comparação? \vspace{7em}

1. Com base em suas respostas acima, faça uma tradução linha a linha da função acima. \vspace{10em}

Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes. 

\newpage

**Exercício**: O exercício abaixo exercita **Chamadas de funções** e **Loops**. 

```asm
Dump of assembler code for function ex4:
   0x05fe <+0>: 	push   %rbx
   0x05ff <+1>: 	mov    %edi,%ebx
   0x0601 <+3>:	    mov    $0x0,%eax
   0x0606 <+8>:	    jmp    0x60f <ex4+17>
   0x0608 <+10>:	mov    %eax,%edi
   0x060a <+12>:	callq  0x5fa <mais_um>
   0x060f <+17>:	cmp    %ebx,%eax
   0x0611 <+19>:	jb     0x608 <ex4+10>
   0x0613 <+21>:	pop    %rbx
   0x0614 <+22>:	retq   
```

1. Quantos argumentos a função acima recebe? Quais seus tipos? E o valor de retorno? Declare a função abaixo. \vspace{5em}

1. A função acima tem um loop. Entre quais instruções? Use setas para identificá-lo. \vspace{5em}

1. É feita uma chamada para `mais_um`. Qual o argumento passado? Onde seu resultado é usado? \vspace{5em}

1. Faça uma tradução linha a linha da função acima usando somente `if+goto` \vspace{10em}

Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes. 

<!--






# Parte 









1. Qual é o resultado da chamada de `func(3)` pelo `main`? \vspace{5em}

2. Escreva abaixo a fórmula usada pelo `LEA` para o cálculo do valor acima.\vspace{5em}

A melhor maneira de identificar qual tipo de uso estamos fazendo é observar os operandos usados no `LEA` e o uso feito de seu resultado. Por isso é  muito importante identificar os parâmetros das funções. Se os operandos representarem parâmetros inteiros (`int` ou `long`) então certamente será um caso de aritmética. Se eles forem ponteiros então se trata do operador `&`.

Em nossos exemplos, `LEA` aparece sempre com o registrador `%rsp` para calcularmos endereços de variáveis na pilha. Logo, a ocorrência de `LEA` com `%rsp` certamente é um caso em que usamos `&`. Além disto, se usamos `LEA` para preencher um registrador usado em um `call` então esse registrador provavelmente representa um argumento ponteiro. 

Veja um outro exemplo abaixo:

~~~{.asm}
0000 <func2>:
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

05fa <prod>:
5fa:   ba 01 00 00 00          mov    $0x1,%edx
5ff:   b8 01 00 00 00          mov    $0x1,%eax
604:   eb 08                   jmp    60e <prod+0x14>
606:   48 0f af c2             imul   %rdx,%rax
60a:   48 83 c2 01             add    $0x1,%rdx
60e:   48 39 fa                cmp    %rdi,%rdx
611:   7c f3                   jl     606 <prod+0xc>
613:   f3 c3                   repz retq

0615 <main>:
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

-->
