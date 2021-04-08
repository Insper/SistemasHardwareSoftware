# 09 - Array em Assembly

A parte final de nossas atividades com Assembly é entender *Arrays*. Já estudamos todo o necessário para lidar com eles:

1. um array é representado por um apontador para seu primeiro elemento. Já estudamos ponteiros e a escrita em memória com `MOV`.
2. ao acessar o elemento `i` de `long *vec` estamos acessando o endereço `&vec[0] + sizeof(long) * i`. A notação de cálculos de endereço de memória faz exatamente isso.

Para iniciar vamos revisar a notação de cálculo de endereços de memória: `D(%reg1, %reg2, S)`, onde

* `D` é um número inteiro que representa um deslocamento constante a partir do endereço guardado em `%reg1`
* `%reg1` contém o endereço do primeiro elemento do vetor
* `%reg2` contém o índice do elemento a ser acessado
* `S` contém o tamanho de cada elemento do vetor e pode ser `1, 2, 4` ou `8`.

O acesso é feito ao endereço `D + %reg1 + S * %reg2`. Ou seja, primeiro computamos o endereço e depois acessamos a memória *no endereço computado*.

!!! question choice
    Supondo que `%rsi=0x24, %rdi=0x8`, o valor final da expressão `(%rsi, %rdi, 4)` é

    - [ ] `0x32`
    - [ ] `0x48`
    - [ ] `0x56`
    - [x] `0x44`

    !!! details "Resposta"
        Tudo está em hexa. A conta é `36 + 4 * 8 = 68`.

!!! question choice
    Supondo que `%rdx=0x44`, o valor da expressão `0x12(%rdx)` é

    - [x] `0x56`
    - [ ] `0x44`
    - [ ] `0x52`

    !!! details "Resposta"
        Tudo está em hexa. A conta é `18 + 68 = 86 = 0x56`.

## Exemplo guiado

Dado o array `int *vec` (guardado em `%rdx`). A atribuição de 5 ao elemento `i` (guardado em `%ecx`) seria traduzida como

```asm
MOVL $0x5, (%rdx, %rcx, 4)
```

!!! Warning "Importante"
    Lembre-se de que apontadores são tipos de dados com tamanho *8 bytes*.


Considerando um vetor `short *vec` e que o endereço do primeiro elemento de `vec` esteja em `%rdi`,

!!! question short
    Qual a instrução usada para mover o conteúdo de `vec[i]` para o registrador `%eax` ?(supondo que o valor de `i` esteja em `%esi`)

    !!! details "Resposta"
        `mov (%rdi, %rsi, 2), %eax`

!!! question short
    Qual a instrução usada para mover `&vec[i]` para o registrador `%eax`?

    **Dica**: como você implementava o operador `&` com variáveis locais?

    !!! details "Resposta"
        `lea (%rdi, %rsi, 2), %eax`

## Exercício 1 - função `soma`

Veja o código abaixo e responda as perguntas.

```asm
Dump of assembler code for function soma:
   0x0000 <+0>:	    mov    $0x0,%edx
   0x0005 <+5>:	    mov    $0x0,%eax
   0x000a <+10>:	jmp    0x15 <soma+21>
   0x000c <+12>:	movslq %edx,%rcx
   0x000f <+15>:	add    (%rdi,%rcx,4),%eax
   0x0012 <+18>:	add    $0x1,%edx
   0x0015 <+21>:	cmp    %esi,%edx
   0x0017 <+23>:	jl     0xc <soma+12>
   0x0019 <+25>:	repz retq
```

!!! question medium
    A função acima usa vários registradores. Para facilitar a descoberta de quais são parâmetros da função anote abaixo cada registrador usado e, ao lado, a linha do primeiro uso e se esse uso foi leitura ou escrita.

!!! question short
    Se o primeiro acesso a registrador é de escrita então ele provavelmente não é um parâmetro. Com base nisto, escreva abaixo a declaração da função acima.

!!! question short
    Sempre que escrevemos a notação de acesso à memória `D(%reg1, %reg2, S)` precisamos usar registradores de `64` bits nos lugares de `reg1` e `reg2`. Com base nisto, explique qual o uso feito do registrador `%edx` e porquê usamos a instrução `movslq` na linha `c`.

!!! question long
    Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

## Acesso a elementos constantes

O acesso a elementos "constantes", como `long v[10]; v[5] = 0;`, não é feito usando a notação acima, pois o compilador já sabe **em tempo de compilação**, qual é o deslocamento necessário para encontrar a posição 6 de `v`.

Considerando o exemplo acima, responda.

!!! question short
    Supondo que `v=0x100`, qual o é o endereço de `v[5]`?

    !!! details "Resposta"
        Cada `long` ocupa 8 bytes, logo o elemento `v[5]` está 40 bytes após o início do vetor. Logo, o endereço de `v[5]` é `0x100 + 0x028 = 0x128`.

!!! question short
    Escreva a instrução usada para mover o valor `0` para `v[5]` (supondo que o endereço do primeiro elemento esteja em `%rdi`).

    !!! details "Resposta"
        `mov $0, 0x28(%rdi)` = Início de `%rdi` + 40 bytes.

!!! tip "Importante"
    O compilador pode (e vai) aplicar diversas otimizações para economizar o máximo possível. Por essa razão, é importante saber calcular os endereços de memória na mão. Assim conseguimos "refazer" o processo que gerou a otimização e entender melhor o código *C* original.

### Exercício 2 - função `func_que_recebe_array`

```asm
Dump of assembler code for function func_que_recebe_array:
   0x0000 <+0>:	    mov    0x4(%rdi),%eax
   0x0003 <+3>:	    add    (%rdi),%eax
   0x0005 <+5>:	    cmp    0x8(%rdi),%eax
   0x0008 <+8>:	    setl   %al
   0x000b <+11>:	movzbl %al,%eax
   0x000e <+14>:	retq
```

!!! question short
    Temos acessos à memória relativos ao endereço passado em `%rdi` nas linhas `0, 3` e `5`. Isto significa que `%rdi` é um ponteiro. Pelos tipos de acessos feitos, você consegue identificar para qual tipo de variável ele aponta?

!!! question short
    Traduza os acessos de memória feitos nas linhas citadas acima para a notação de acesso a arrays em *C*.

!!! question medium
    Com base no respondido acima, faça uma versão em *C* legível do código asembly acima. Se ajudar, faça uma tradução linha a linha do Assembly e depois torne-a legível.

## Exercício 3 - função `first_neg`

Veja agora o código abaixo e responda.

```asm
Dump of assembler code for function first_neg:
   0x0000 <+0>:	    mov    $0x0,%eax
   0x0005 <+5>:	    cmp    %esi,%eax
   0x0007 <+7>:	    jge    0x17 <first_neg+23>
   0x0009 <+9>:	    movslq %eax,%rdx
   0x000c <+12>:	cmpl   $0x0,(%rdi,%rdx,4)
   0x0010 <+16>:	js     0x17 <first_neg+23>
   0x0012 <+18>:	add    $0x1,%eax
   0x0015 <+21>:	jmp    0x5 <first_neg+5>
   0x0017 <+23>:	repz retq
```


!!! question medium
    A função acima usa vários registradores. Para facilitar a descoberta de quais são parâmetros da função anote abaixo cada registrador usado e, ao lado, a linha do primeiro uso e se esse uso foi leitura ou escrita.

!!! question short
    Desenhe setas indicando o destino dos pulos no código acima. Você consegue idenfiticar quais estruturas de controle? Entre quais linhas?

!!! question long
    Faça uma versão em *C* usando `if-goto` do código acima.

!!! question medium
    Transforme seu código em uma versão legível.


