# 07 - Loops

## Arquivo `ex1`

Utilize como base o código assembly abaixo (arquivo `ex1`) e responda os itens.

```asm
Dump of assembler code for function soma_2n:
   0x066a <+0>:	    mov    $0x1,%eax
   0x066f <+5>:	    jmp    0x676 <soma_2n+12>
   0x0671 <+7>:	    shr    %edi
   0x0673 <+9>:	    add    $0x1,%eax
   0x0676 <+12>:	cmp    $0x1,%edi
   0x0679 <+15>:	ja     0x671 <soma_2n+7>
   0x067b <+17>:	repz retq

```

!!! exercise text short
    Localize no código acima as instruções de saltos (`jmp` ou condicionais `j*`). Desenhe setas indicando para qual linha do código elas pulam.

    !!! answer
        Há um salto de `soma_2n <+5>` para `soma_2n <+12>` e outro de `soma_2n <+15>` para `soma_2n <+7>`

!!! exercise text short
    Analise o fluxo de saltos do seu código. Existe um loop? Entre quais linhas?

    !!! answer
        O loop ocorre entre as linhas `+5` e `+15`. 

!!! exercise choice
    Qual é a condição do loop acima? Ou seja, qual condição precisa ser verdade para que o loop **continue rodando**?

    - [x] `%edi > 1`
    - [ ] `%edi < 1`
    - [ ] `%edi > 0`
    - [ ] `%eax > 1`

    !!! answer
        Sempre comparamos o segundo em relação ao primeiro. Logo, fazemos `%edi > 1`. A instrução `ja` representa a comparação **jump above**, que é uma comparação de `>` feita entre variáveis `unsigned`

!!! exercise text short
    Com base na sua resposta acima, como você escreveria esse loop como um `while`?

    !!! answer
        Considerando que o primeiro argumento da função se chama `int arg1`, seria `while(arg1 > 1)`.

!!! exercise text long
    Comece fazendo uma versão *C* usando somente `if-goto`
    
    !!! answer
        ```C
        int soma_2n(unsigned int a) {
            int res = 1;
            goto verifica;
            
            faz_algo:
            a = a >> 1;
            res += 1;

            verifica:
            if (a > 1) {
                goto faz_algo;
            }

            return res;
        }
        ```

!!! exercise text long
    Transforme a construção que você fez acima em um código usando `while`.
    !!! answer
        ```C
        int soma_2n(unsigned int a) {
            int res = 1;
            while (a > 1) {
                a = a/2;
                res++;
            }

            return res;
        }
        ```

---------------

## Exercícios para entrega

Vamos agora exercitar o que vimos na aula expositiva. Os exercícios abaixo estão no repositório de atividades e as perguntas no handout tem o objetivo de ajudar a compreender códigos cada vez mais complexos.

### Arquivo `ex2`

Leia o código assembly abaixo e responda.

```asm
Dump of assembler code for function soma_n:
   0x066a <+0>:	    mov    $0x0,%edx
   0x066f <+5>:	    mov    $0x0,%eax
   0x0674 <+10>:	jmp    0x67f <soma_n+21>
   0x0676 <+12>:	movslq %edx,%rcx
   0x0679 <+15>:	add    %rcx,%rax
   0x067c <+18>:	add    $0x1,%edx
   0x067f <+21>:	cmp    %edi,%edx
   0x0681 <+23>:	jl     0x676 <soma_n+12>
   0x0683 <+25>:	repz retq

```

!!! exercise text short
    Desenhe as flechas indicando o destino de cada instrução de pulo (`jmp` ou `j*`).

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text short
    Escreva abaixo o cabeçalho da função `soma_n`. **Dica**: procure por registradores que são lidos *antes* de serem escritos.

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text medium
    Faça a tradução do código acima para *C* usando somente `if-goto`

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text medium
    Converta o código acima para uma versão legível em *C*.

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```


### Arquivo `ex3`

```asm
Dump of assembler code for function ex3:
    0x1139 <+0>:     mov    $0x0,%ecx
    0x113e <+5>:     mov    $0x0,%r8d
    0x1144 <+11>:    jmp    0x114a <ex4+17>
    0x1146 <+13>:    add    $0x1,%rcx
    0x114a <+17>:    cmp    %rdi,%rcx
    0x114d <+20>:    jge    0x1161 <ex4+40>
    0x114f <+22>:    mov    %rcx,%rax
    0x1152 <+25>:    cqto
    0x1154 <+27>:    idiv   %rsi
    0x1157 <+30>:    test   %rdx,%rdx
    0x115a <+33>:    jne    0x1146 <ex4+13>
    0x115c <+35>:    add    %rcx,%r8
    0x115f <+38>:    jmp    0x1146 <ex4+13>
    0x1161 <+40>:    mov    %r8,%rax
    0x1164 <+43>:    retq
```

!!! exercise text short
    Quantos argumentos a função acima recebe? Quais seus tipos?

    **Dica**: não se esqueça de buscar por registradores que são lidos antes de serem escritos.

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text short
    A função retorna algum valor? Se sim, qual seu tipo?

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text short
    A função acima combina loops e condicionais. Desenhe setas para onde as instruções de `jmp` apontam.

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text short
    Com base no exercício anterior, entre quais linhas o loop ocorre? E a condicional?

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text short
    O loop acima tem uma variável contadora. Ela está em qual registrador? Qual seu tipo?

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text short
    Revise o funcionamento da instrução `idiv`. Em qual registrador é armazenado o resultado da divisão? E o resto?

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text short
    Qual a condição testada na condicional?

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text long
    Escreva uma versão do código acima usando somente `if-goto`.

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```

!!! exercise text long
    Escreva uma versão legível do código acima.

    !!! answer
        ```C
        // Atividade para entrega!
        // Confira nos atendimentos ou chame os professores!
        ```