# 06 - Condicionais e funções

Na aula de hoje vamos revisar e praticar os conceitos de funções e condicionais em Assembly. Teremos exercícios simples de cada assunto e no fim alguns exercícios para entrega que juntam coisas diferentes.

## Funções e aritmética com `LEA`

Todos os exercícios da revisão serão feitos com o arquivo `exemplo1` (compilado a partir de `exemplo1.c`). Vamos examinar tanto a função `main` quanto a função `exemplo1`.

Compile com:

<div class="termy">

```console
$ gcc -Og -Wall -std=c99 exemplo1.c -o exemplo1
```

</div>

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
   0x01163 <+8>:	mov    $0x6,%r9d
   0x01169 <+14>:	mov    $0x5,%r8d
   0x0116f <+20>:	mov    $0x4,%ecx
   0x01174 <+25>:	mov    $0x3,%edx
   0x01179 <+30>:	mov    $0x2,%esi
   0x0117e <+35>:	mov    $0x1,%edi
   0x01183 <+40>:	call   0x1149 <exemplo1>
   0x01188 <+45>:	lea    0xa(%rax),%esi
```

!!! exercise choice "Pergunta"
    O valor do primeiro argumento da função é

    - [ ] 6
    - [x] 1

    !!! answer
        A ordem dos parâmetros segue é sempre a mesma vista na [aula 04](../04-funcoes-mov). Mesmo que as instruções estejam em ordem diferente, `%edi` (ou uma de suas partes) é sempre o primeiro parâmetro.


!!! exercise text short
    A instrução `call` realiza chamadas de função. Traduza a chamada de função acima para *C*.

    !!! answer
        `exemplo1(1, 2, 3, 4, 5, 6)`

Vamos agora analisar o código de `exemplo1`:

```asm
Dump of assembler code for function exemplo1:
    0x01149 <+0>:	endbr64 
    0x0114d <+4>:	add    %esi,%edi
    0x0114f <+6>:	add    %edx,%edi
    0x01151 <+8>:	add    %ecx,%edi
    0x01153 <+10>:	add    %r8d,%edi
    0x01156 <+13>:	lea    (%rdi,%r9,1),%eax
    0x0115a <+17>:	ret
```

!!! exercise text short
    Quantos parâmetros a função acima recebe? Quais seus tipos? Ela retorna algum valor? Se sim, qual seu tipo?

    !!! answer
        Pelos registradores utilizados, percebemos que a função tem seis parâmetros, todos `int`.
        O retorno também é `int`.

!!! exercise text short
    Declare a função acima com base na sua resposta anterior.

    !!! answer
        `int exemplo1(int a, int b, int c, int d, int e, int f);`

!!! exercise text long
    O que faz o conjunto de instruções `add` nas linhas `+4` até `+10`? Escreva uma expressão em *C* equivalente.

    !!! answer
        Ela soma os primeiros 5 argumentos: `a + b + c + e`.

Vemos na linha `exemplo1+13` que colocamos um valor no registrador `%eax` e depois finalizamos a função usando `ret`. Este é o segundo ponto que nunca muda: **o valor de retorno de toda função é colocado no registrador `%rax`** (ou uma de suas partes menores). Neste exemplo, a instrução usada foi o `LEA` que relembraremos na seção a seguir.

### Operações aritméticas usando `LEA`

Se usada de maneira literal, a instrução LEA (Load Effective Address) serve para calcular o endereço de uma variável local e é equivalente ao operador `&` em *C*. Porém, ela é frequentemente "abusada" para fazer aritmética. Um ponto importante quando usamos `LEA` é que todos os operandos são registradores de `64` bits.

!!! tip "Regra geral"

    1. Se `LEA` for usada com o registrador `%rsp` então ela sempre representa o operador `&`
    1. Se os registradores envolvidos foram usados como números inteiros em instruções anteriores, então ela representa uma conta com os valores dos registradores.

Vejamos o exemplo da função `exemplo1` acima:

```asm
    lea    (%rdi,%r9,1),%eax
   0x01156 <+13>:	lea    (%rdi,%r9,1),%eax
```

No exemplo acima `LEA` é usada para fazer aritmética. Sabemos disso pois, na chamada traduzida na parte anterior, elas recebem números inteiros (`%r9d = 6` e `%edi = 1` mais o resultado de sucessivas somas). Seu primeiro argumento segue a seguinte lógica

```asm
C(%R1, %R2, S)
```

* `C` é uma constante
* `%R1` é um registrador
* `%R2` é um registrador (pode ser igual a `%R1`)
* `S` é `1, 2, 4`  ou `8` (todos os tamanhos possíveis de registradores inteiros)

A operação acima calcula `C + %R1 + (%R2 * S)`. A operação `LEA` **nunca acessa a memória**, apenas move o resultado deste cálculo para o registrador destino. **Qualquer outra operação que use a sintaxe acima está fazendo um acesso a memória. `LEA` é a única exceção!**


!!! exercise text short
    Traduza a operação abaixo para *C*

    ```asm
       0x01156 <+13>:	lea    (%rdi,%r9,1),%eax
    ```

    !!! answer
        Supondo que `aux = a+b+c+d+e` já foi calculado com o uso das instruções `ADD`, então o `LEA` calcula `aux + f*1`.

!!! exercise text long
    Com estas informações em mãos, traduza `exemplo1` para *C*

    ```asm
    Dump of assembler code for function exemplo1:
    0x01149 <+0>:	endbr64 
    0x0114d <+4>:	add    %esi,%edi
    0x0114f <+6>:	add    %edx,%edi
    0x01151 <+8>:	add    %ecx,%edi
    0x01153 <+10>:	add    %r8d,%edi
    0x01156 <+13>:	lea    (%rdi,%r9,1),%eax
    0x0115a <+17>:	ret
    ```
    !!! answer
        Confira no arquivo `exemplo1.c`

### Retorno de funções

Vamos terminar nossa revisão analisando novamente a chamada de `exemplo1` no `main`:

```asm
   0x01163 <+8>:	mov    $0x6,%r9d
   0x01169 <+14>:	mov    $0x5,%r8d
   0x0116f <+20>:	mov    $0x4,%ecx
   0x01174 <+25>:	mov    $0x3,%edx
   0x01179 <+30>:	mov    $0x2,%esi
   0x0117e <+35>:	mov    $0x1,%edi
   0x01183 <+40>:	call   0x1149 <exemplo1>
   0x01188 <+45>:	lea    0xa(%rax),%esi
```

Anteriormente já vimos que o `call` e os `mov` s acima fazem a chamada `exemplo1(1,2,3,4,5,6)` em *C*.
A linha de baixo realiza uma operação aritmética com `%rax`.


!!! exercise text short
    Considerando que `%rax` armazena o valor de retorno de uma função, qual seria a tradução para *C* do bloco de código acima?

    !!! answer
        int esi = exemplo1(1, 2, 3, 4, 5, 6) + 10;


## Exercícios combinados

!!! warning
    Todos os exercícios desta seção são para entrega. Vocês podem se conversar para fazê-los, mas cada um deve criar sua própria solução do zero. Todos os exercícios já estão disponíveis no seu repositório de entregas da disciplina em `atv/04-condicionais-funcoes`. Leia o `README` dentro da pasta para mais informações.


### Função `ex1`: **Aritmética** e **Expressões booleanas**.

```asm
   Dump of assembler code for function ex1:
   0x000 <+0>:	endbr64
   0x004 <+4>:	lea    (%rdi,%rsi,1),%rax
   0x008 <+8>:	lea    (%rax,%rdx,4),%rcx
   0x00c <+12>:	imul   %rdi,%rdi
   0x010 <+16>:	lea    (%rdi,%rsi,2),%rax
   0x014 <+20>:	add    %rax,%rdx
   0x017 <+23>:	cmp    %rdx,%rcx
   0x01a <+26>:	setge  %al
   0x01d <+29>:	movzbl %al,%eax
   0x020 <+32>:	ret
```

!!! exercise text long
    Quantos argumentos a função acima recebe? Quais seus tipos? Declare a função abaixo.

!!! exercise text long
    As instruções `LEA` acima representam operações aritméticas ou a operação *endereço de* `&`? Como você fez esta identificação? .

!!! exercise text long
    Traduza as operações das linhas `ex1+0` até `ex1+16` para *C*

!!! exercise text long
    Nas linhas `ex1+23` e `ex1+26` é feita uma comparação. Qual e entre quais registradores? Onde é armazenado este resultado?

!!! exercise text long
    O quê faz a instrução `movzbl` em `ex1+29`? Juntando com a resposta da pergunta acima, traduza as instruções `ex1+23` até `ex1+32` para *C*.

!!! example
    Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes.

### Função `ex2`: **Chamadas de funções** e **Condicionais**.

Quando analisar o código do ex2 no gdb, utilize o arquivo `ex2_ref` para visualizar corretamente as chamadas de funções. Seria uma boa também consultar as *relocation entries* no terminal com `objdump -r ex2.o`.

```asm
Dump of assembler code for function ex2:
   0x01132 <+0>:	endbr64
   0x01136 <+4>:	push   %rbx
   0x01137 <+5>:	mov    %rdi,%rbx
   0x0113a <+8>:	mov    %rsi,%rdi
   0x0113d <+11>:	call   0x1129 <vezes2>
   0x01142 <+16>:	cmp    %rbx,%rax
   0x01145 <+19>:	jle    0x114a <ex2+24>
   0x01147 <+21>:	add    %rbx,%rbx
   0x0114a <+24>:	add    %rbx,%rax
   0x0114d <+27>:	pop    %rbx
   0x0114e <+28>:	ret 
```

!!! exercise text long
    Quantos argumentos a função acima recebe? Quais são seus tipos? Declare-a abaixo.

Vamos começar trabalhando na linha `ex2+11`, na instrução `call vezes2` . A chamada necessita usar o registrador `%rdi`, mas ele contém o primeiro argumento de `ex2`.

!!! exercise text short
    Em qual registrador é guardado o primeiro argumento de `ex2`? Isso é feito antes da chamada `call`.

!!! exercise text short
    Qual variável é passada como argumento para a função `vezes2` ?

!!! exercise text short
    Escreva abaixo a invocação de `vezes2`.


Você deve ter notado as instruções `push/pop %rbx` no começo/fim da função. Toda função pode usar os registradores de argumentos (vistos na parte 1) e o de valor de retorno como quiserem. Se precisarem mexer nos outros registradores a prática é salvá-los na pilha no começo da função e restaurá-los no fim. Assim não importa o que a função faça, para a função chamadora é como se não houvesse havido nenhuma modificação nos outros registradores.

Vamos agora olhar a condicional na linha `ex2+16`.

!!! exercise text short
    Após a chamada `call`, qual o conteúdo de `%rax`?

!!! exercise text short
    Juntando suas respostas nas questões de cima, qual é a comparação feita nas linhas `ex2+16, ex2+19` ?

!!! exercise text long
    Com essas informações em mãos, faça uma tradução do código acima para *C* usando somente `if+goto`.

!!! example
    Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes.

### Função `ex3`: **Ponteiros** e **Expressões booleanas**.

```asm
Dump of assembler code for function ex3:
   0x000 <+0>:	endbr64
   0x004 <+4>:	cmp    %rsi,%rdi
   0x007 <+7>:	setl   %al
   0x00a <+10>:	movzbl %al,%eax
   0x00d <+13>:	mov    %eax,(%rdx)
   0x00f <+15>:	sete   %al
   0x012 <+18>:	movzbl %al,%eax
   0x015 <+21>:	mov    %eax,(%rcx)
   0x017 <+23>:	setg   %al
   0x01a <+26>:	movzbl %al,%eax
   0x01d <+29>:	mov    %eax,(%r8)
   0x020 <+32>:	ret
```

!!! exercise text long
    Quantos argumentos a função acima recebe? De quais tipos? Declare-a abaixo.

!!! exercise text long
    A função acima faz várias comparações. Liste quais e entre quais argumentos.

!!! exercise text long
    Onde é armazenado o resultado de cada comparação?

!!! exercise text long
    Com base em suas respostas acima, faça uma tradução linha a linha da função acima.

!!! example
    Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes.


### Função `ex4`: **Ponteiros** e **Expressões booleanas**.

```asm
Dump of assembler code for function ex4:
   0x00a <+0>:	endbr64 
   0x00e <+4>:	cmp    $0x11,%di
   0x012 <+8>:	jle    0x21 <ex4+23>
   0x014 <+10>:	sub    $0x41,%esi
   0x017 <+13>:	cmp    $0x1,%sil
   0x01b <+17>:	ja     0x29 <ex4+31>
   0x01d <+19>:	lea    -0x11(%rdi),%eax
   0x020 <+22>:	ret    
   0x021 <+23>:	mov    $0x12,%eax
   0x026 <+28>:	sub    %edi,%eax
   0x028 <+30>:	ret    
   0x029 <+31>:	mov    $0xffffffff,%eax
   0x02e <+36>:	ret 

```

!!! exercise text long
    Quantos argumentos a função acima recebe? De quais tipos? Declare-a abaixo.

!!! exercise text long
    A função acima faz várias comparações. Liste quais e entre quais argumentos.

!!! exercise text long
    Onde é armazenado o resultado de cada comparação?

!!! exercise text long
    Com base em suas respostas acima, faça uma tradução linha a linha da função acima.

!!! example
    Usando as perguntas acima preencha o arquivo de solução no repositório e execute os testes.

