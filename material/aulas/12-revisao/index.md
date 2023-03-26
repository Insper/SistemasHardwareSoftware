# 12 - Revisão

<script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>


Na aula de hoje iremos revisar nossas atividades com Assembly e representação de inteiros.

Quando tiver dúvidas, chame os professores!

!!! Warning "Importante"
    Esta aula tem duas partes:

    - **Exercícios de revisão** (`ex1.c`, `ex2.c`, `ex3.c` e `ex4.c`)
        - Siga o roteiro para desenvolvê-los
    - **Simulado de prova**
        - Veja mais detalhes no final do roteiro!

## Ex1.c

Abra o código-fonte `ex1.c` e confira a função `main`. Compile e execute o exercício 1. Em seguida, resposta:

!!! exercise text short
    O valor apresentado na saída confere com o presente no código? Por que isto acontece?

    !!! answer
        O valor -1 em complemento de 2 é representado como uma sequência de 1's. Ao ser atribuído em uma unsigned short, teremos dezesseis 1's, mas que serão interpretados como unsigned. Somando $2^0 + 2^1 + \dots + 2^{15} = 65535$


!!! exercise text short
    Qual o maior valor que pode ser armazenado em uma variável **unsigned short**?

    !!! answer
        A variável será de 2 bytes sem sinal, assim o maior valor é $2^{16}-1 = 65535$

!!! exercise text short
    O que acontece quando tentamos armazenar um valor maior que o suportado pelo tipo de dados? Ex: atribuir `80000` para uma **unsigned short**.

    !!! answer
        Apenas os 16 bits menos significativos serão considerados.


## Ex2.c

Neste exercício iremos fazer engenharia reversa de Assembly para C. Os códigos-fonte estão disponíveis no repositório, mas evite abri-los antes de ter feito pelo menos uma primeira versão da engenharia reversa.

Compile o `ex2.c` com

<div class="termy">

```console
$ gcc -Wall -std=c99 -Og ex2.c -c -o ex2.o
```

</div>

Abra o arquivo `ex2.o` com o **gdb** sem abrir o código-fonte e responda:

!!! exercise text short
    Liste as variáveis globais e funções existentes.

    !!! answer
        Funções `func1` e `func2`. Sem variáveis globais.

Analise a função `func1` com o gdb e responda:

!!! exercise text short
    Com base nos registradores utilizados, escreva a assinatura da função `func1`.

    !!! answer
        ```C
        void func1(unsigned short *vec)
        ```
        A partir de um ponteiro armazenado em `%rdi`, são feitas várias atribuições espaçadas em dois bytes, indicando ser um ponteiro para `short`.        

!!! exercise text long
    Em `movw   $0x0,(%rdi)`, qual a operação realizada e o que significa o trecho `(%rdi)`?

    !!! answer
        A operação é `vec[0] = 0` ou `*vec = 0`. Como a operação é um `MOV`, então `(%rdi)` representa uma dereferenciação de ponteiro.
    
!!! tip
    Veja a seção **Acesso a elementos constantes** da aula **09 - Arrays**

!!! exercise text short
    Em `movw   $0x14,0x4(%rdi)`, qual a operação realizada e o que significa o trecho `0x4(%rdi)`?

    !!! answer
        A operação é `vec[2] = 20`. Em `0x4(%rdi)`, indicamos que queremos acessar o endereço **%rdi + 4 bytes**.

!!! tip
    Acese na aula **05-Condicionais** a explicação sobre as variântes da instrução `mov`

!!! exercise text  long
    Faça uma versão legível em *C* da função `func1`.

    !!! answer
        ```C
        void func1(unsigned short *vec) {
            vec[0] = 0;
            vec[1] = 10;
            vec[2] = 20;
        }
        ```

Analise a função `func2` com o gdb e responda:

!!! exercise text short
    Com base nos registradores utilizados, escreva a assinatura da função `func2`.

    !!! answer
        ```C
        void func2(int *vec, int n)
        ```
        Caso restem dúvidas, chame os professores.

!!! exercise text short
    Qual a operação realizada em `lea    (%rax,%rax,4),%edx` na função `func2`?

    !!! answer
        É uma operação aritmética onde o valor armazenado em `%rax` é multiplicado por 5 e armazenado em `%edx`.

!!! exercise text short
    Qual a operação realizada em `add    %edx,%edx` na função `func2`?

    !!! answer
        É uma operação aritmética onde o valor armazenado em `%edx` é somado consigmo mesmo e armazenado em `%edx`. Isto é equivalente a fazer `var = var * 2`.


!!! exercise text short
    Você conseguiria agregar as operações `lea    (%rax,%rax,4),%edx` e `add    %edx,%edx` em uma única operação aritmética mais simples?

    !!! answer
        Supondo que `%eax` representa a variável `i`, então a junção das duas operações é equivalente a fazer `i * 10`, cujo resultado é armazenado em `%edx`.


!!! exercise text long
    Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

    !!! answer
        Versão `if-goto`:
        ```C
        void func2(int *vec, int n) {
            int i = 0;
            int aux;

            loop:
                if (i >= n) {
                    goto retorna:
                }

                aux = i * 5;
                aux = aux + aux;
                
                vec[i] = aux;

                i = i + 1;
                
                goto loop;

            retorna:
                return;
        }
        ```

        Versão `C`:
        ```C
        void func2(int *vec, int n) {
            for (int i = 0; i < n; i++) {
                vec[i] = i * 10;
            }
        }
        ```
        Caso restem dúvidas, chame os professores.

## Ex3.c

Neste exercício iremos fazer engenharia reversa de Assembly para C. Os códigos-fonte estão disponíveis no repositório, mas evite abri-los antes de ter feito pelo menos uma primeira versão da engenharia reversa.

Compile o `ex3.c` com:

<div class="termy">

```console
$ gcc -Wall -std=c99 -Og ex3.c -o ex3
```

</div>

Abra o arquivo `ex3` com o **gdb** sem abrir o código-fonte e responda:

!!! exercise text short
    Liste as funções e variáveis globais disponíveis.

    !!! answer
        Variável global `v_global`. Funções `func1`, `func2`, `func3`, `func4` e `main`.

!!! exercise text long
    Faça a tradução das funções `func1` e `func2`. Existe alguma semelhança?

    !!! answer
        Ambas fazem operações com registradores. Porém `func2` faz a leitura de algum valor de memória e armazenando no retorno da função, uma variável global. Já `func1` apenas faz uma operação aritmética com o parâmetro recebido.

        ```C
        int func1(int n) {
            int x = 10;
            return x + n;
        }

        int func2(int n) {
            return v_global + n;
        }
        ```

!!! tip
    Fique atento a chamadas de variáveis globais. Utilize o comando `x` para imprimir o conteúdo de um endereço. Veja mais em https://sourceware.org/gdb/current/onlinedocs/gdb/Memory.html

    Exemplo:
        ```
        x/d  0x100

        x/s  0x100
        ```

!!! exercise text short
    Defina a assinatura da função `func3` e faça sua tradução para C.

    !!! answer
        ```C
        int func3(int n, int mult) {
            return v_global + n * mult;
        }
        ```


!!! exercise text long
    Defina a assinatura da função `func4`. Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

    !!! answer
        Versão `if-goto`:
        ```C
        void func4() {
            res = func1(5);

            if (res <= 20) {
                goto faz_algo;
            }

            printf("O novo valor eh maior que 20");

            retorna:
                return;

            faz_algo:
                printf("O novo valor nao eh maior que 20");
                goto retorna;
                
        }
        ```

        Versão `C`:
        ```C
        void func4() {
            int aux = func1(5);
            if (aux > 20) {
                printf("O novo valor eh maior que 20");
            } else {
                printf("O novo valor nao eh maior que 20");
            }
        }
        ```

## Ex4.c

Neste exercício iremos fazer engenharia reversa de Assembly para C. Os códigos-fonte estão disponíveis no repositório, mas evite abri-los antes de ter feito pelo menos uma primeira versão da engenharia reversa.

Compile o `ex4.c` com:

<div class="termy">

```console
$ gcc -Wall -std=c99 -fno-stack-protector -Og ex4.c -o ex4`
```

</div>

Abra o arquivo `ex4` com o **gdb** sem abrir o código-fonte e responda:

!!! exercise text long
    Defina a assinatura da função `ex4`. Faça uma versão em *C* do código acima usando somente `if-goto`. Escreva, então, ao lado desta versão um código legível em *C*.

    !!! answer
        Versão `if-goto`:
        ```C
        int ex4() {
            unsigned short n;
            int ret;
            int i;
            int aux;

            scanf("%hu", &n);

            loop:
                aux = n;

                if (aux <= i) {
                    goto retorna;
                }

                ret = ret + i*4;
                i = i+1;

            goto loop;

            retorna:
                return ret;
            
        }
        ```

        Versão `C`:
        ```C
        #include <stdio.h>

        int ex4() {
            unsigned short n;

            scanf("%hu", &n);

            int res = 0;
            int i = 1;
            
            while (i < n) {
                res += (i*4);
                i++;
            }

            return res;
        }

        int main() {
            return 0;
        }
        ```

!!! tip
    Observe sempre as chamadas de variáveis globais e strings (relativos a `%rip`) e acessos à stack (relativos a `%rsp`).


## Simulado de prova

Além dos exercícios de revisão feitos na aula, você encontrará no repositório da disciplina um arquivo `simulado_ai.zip`.

Na AI, vocês receberão um arquivo semelhante a este. No dia da prova, você terá que baixar o zip, descompactar, resolver os exercícios, compactar novamente e anexar no Blackboard.

!!! tip
    Leia o `README.md` ou `README.html` para saber o que é esperado em cada questão!

!!! tip
    Leia o `README.md` ou `README.html` para saber como você será avaliado!