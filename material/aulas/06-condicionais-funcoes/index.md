# 06 - Condicionais e funções

Na aula de hoje vamos revisar e praticar os conceitos de funções e condicionais em Assembly. Teremos exercícios simples de cada assunto e no fim alguns exercícios para entrega que juntam coisas diferentes.

## Funções e aritmética com `LEA`

Todos os exercícios da revisão serão feitos com o arquivo `exemplo1` (compilado a partir de `exemplo1.c`). Vamos examinar tanto a função `main` quanto a função `exemplo1`.

### Chamadas de funções

As chamadas de função são feitas usando a seguinte ordem para os argumentos inteiros:

1. `%rdi`
2. `%rsi`
3. `%rdx`
4. `%rcx`
5. `%r8`
6. `%r9`

**Esta ordem nunca muda**. Veja abaixo um exemplo de chamada de função tirado do `main` de `exemplo1`.

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

!!! question choice
    O valor do primeiro argumento da função é

    - [ ] 6
    - [x] 1

    !!! details "Resposta"
        A ordem dos parâmetros segue é sempre a mesma vista na [aula 04](/aulas/04-funcoes-mov). Mesmo que as instruções estejam em ordem diferente, `%edi` (ou uma de suas partes) é sempre o primeiro parâmetro.

!!! question short
    A instrução `call` realiza chamadas de função. Traduza a chamada de função acima para *C*.

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

!!! question short
    Quantos parâmetros a função acima recebe? Quais seus tipos? Ela retorna algum valor? Se sim, qual seu tipo?

!!! question short
    Declare a função acima com base na sua resposta anterior.

    ??? details "Resposta"
        int exemplo1(int a, int b, int c, int d, int e, int f);

!!! question medium
    O que faz o conjunto de instruções `add` nas linhas `+0` até `+6`? Escreva uma expressão em *C* equivalente.

    ??? details "Resposta"
        Ela soma os primeiros 5 argumentos: `a + b + c + e`.

Vemos na linha `exemplo1+9` que colocamos um valor no registrador `%eax` e depois finalizamos a função usando `retq`. Este é o segundo ponto que nunca muda: **o valor de retorno de toda função é colocado no registrador `%rax`** (ou uma de suas partes menores). A instrução usada é o `LEA` que veremos na seção a seguir.

### Operações aritméticas usando `LEA`

Se usada de maneira literal, a instrução LEA (**L**oad **E**ffective **A**ddress) serve para calcular o endereço de uma variável local e é equivalente ao operador `&` em *C*. Porém, ela é frequentemente "abusada" para fazer aritmética. Um ponto importante quando usamos `LEA` é que todos os operandos são registradores de `64` bits.

!!! tip "Regra geral":

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

!!! question short
    Traduza a operação abaixo para *C*

    ```asm
       0x0653 <+9>:	    lea    (%rcx,%r9,1),%eax
    ```

!!! question medium
    Com estas informações em mãos, traduza `exemplo1` para *C*

    ```asm
    Dump of assembler code for function exemplo1:
       0x064a <+0>:	    add    %esi,%edi
       0x064c <+2>:	    add    %edi,%edx
       0x064e <+4>:	    add    %edx,%ecx
       0x0650 <+6>:	    add    %r8d,%ecx
       0x0653 <+9>:	    lea    (%rcx,%r9,1),%eax
       0x0657 <+13>:	retq
    ```

    ??? details "Resposta"
        Confira no arquivo `exemplo1.c`

### Retorno de funções

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


!!! question short
    Considerando que `%rax` armazena o valor de retorno de uma função, qual seria a tradução para *C* do bloco de código acima?

    ??? details "Resposta"
        int esi = exemplo1(1, 2, 3, 4, 5, 6) + 10;


## Exercícios combinados

!!! warning
    Todos os exercícios desta seção são para entrega. Vocês podem se conversar para fazê-los, mas cada um deve criar sua própria solução do zero. Todos os exercícios já estão disponíveis no repositório de entregas na pasta `03-condicionais-funcoes`.


### Arquivo `ex1`: **Aritmética** e **Expressões booleanas**.

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

!!! question short
    Quantos argumentos a função acima recebe? Quais seus tipos? Declare a função abaixo.

!!! question short
    As instruções `LEA` acima representam operações aritméticas ou a operação *endereço de* `&`? Como você fez esta identificação? .

!!! question short
    Traduza as operações das linhas `ex1+0` até `ex1+12` para *C*

!!! question short
    Nas linhas `ex1+19` e `ex1+22` é feita uma comparação. Qual e entre quais registradores? Onde é armazenado este resultado?

!!! question short
    O quê faz a instrução `movzbl` em `ex1+25`? Juntando com a resposta da pergunta acima, traduza as instruções `ex1+19` até `ex1+28` para *C*.


!!! example
    Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes.

### Arquivo `ex2`: **Chamadas de funções** e **Condicionais**.

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

!!! question short
    Quantos argumentos a função acima recebe? Quais são seus tipos? Declare-a abaixo.

Vamos começar trabalhando na linha `ex2+7`, na instrução `call vezes2` . A chamada necessita usar o registrador `%rdi`, mas ele contém o primeiro argumento de `ex2`.

!!! question short
    Em qual registrador é guardado o primeiro argumento de `ex2`? Isso é feito antes da chamada `call`.

!!! question short
    Qual variável é passada como argumento para a função `vezes2` ?

!!! question short
    Escreva abaixo a invocação de `vezes2`.


Você deve ter notado as instruções `push/pop %rbx` no começo/fim da função. Toda função pode usar os registradores de argumentos (vistos na parte 1) e o de valor de retorno como quiserem. Se precisarem mexer nos outros registradores a prática é salvá-los na pilha no começo da função e restaurá-los no fim. Assim não importa o que a função faça, para a função chamadora é como se não houvesse havido nenhuma modificação nos outros registradores.

Vamos agora olhar a condicional na linha `ex2+12`.

!!! question short
    Após a chamada `call`, qual o conteúdo de `%rax`?

!!! question short
    Juntando suas respostas nas questões de cima, qual é a comparação feita nas linhas `ex2+12, ex2+15` ?

!!! question medium
    Com essas informações em mãos, faça uma tradução do código acima para *C* usando somente `if+goto`.

!!! example
    Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes.

### Arquivo `ex3`: **Ponteiros** e **Expressões booleanas**.

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

!!! question short
    Quantos argumentos a função acima recebe? De quais tipos? Declare-a abaixo.

!!! question short
    A função acima faz várias comparações. Liste quais e entre quais argumentos.

!!! question short
    Onde é armazenado o resultado de cada comparação?

!!! question short
    Com base em suas respostas acima, faça uma tradução linha a linha da função acima.

!!! example
    Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes.

