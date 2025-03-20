# 10 - Alocação Dinâmica de Memória

<script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>


## Exercícios básicos

!!! example "Hora de compilar!"
    Abra o arquivo *ex1.c* em um editor e compile-o usando as flags da disciplina.

<div class="termy">

```console
$ gcc -Og -Wall -std=c99 ex1.c -o ex1
```

</div>

**Sem rodar o programa**, responda as questões abaixo.

!!! exercise text short
    Analisando seu código-fonte, o que este programa faz?

    !!! answer
        Aloca um vetor, preenche com $0,1,...,n$ e imprime!

!!! exercise text short
    Na execução deste programa, o que acontece se `malloc` falhar?

    !!! answer
        A função de alocação irá retornar `NULL`, mas nenhuma verificação está sendo feita.

!!! exercise text short
    O seu programa libera toda memória que aloca? Se não, aponte onde ele deveria fazer isto.

    !!! answer
        Cada valor retornado por `malloc` deve ser liberado usando a função `free`. No caso, vemos que `vetor` não foi liberado após seu uso.
        Isto deveria ser feito na linha 26.


------

Agora execute o programa acima e responda as questões abaixo.

!!! exercise text short
    Ocorreu algum problema durante a execução?

    !!! answer
        A resposta aqui é provavelmente não. Porém, isso não significa que o programa está correto, apenas que se ocorreu um erro ele não foi suficientemente grave para finalizar o programa.

!!! exercise text short
    O comportamento de seu programa muda conforme N muda? Começe com `N=10` e vá incrementando de um em um. Você consegue explicar por que? Discuta com seu grupo e valide sua resposta com o professor.

    !!! answer
        Ao chegar em `N=14` seu programa deverá magicamente dar problemas e deve voltar a funcionar com `N=15`. Este é um dos grandes problemas de programas com erro de memória: seu comportamento é imprevisível.

!!! exercise text short
    Existem três problemas no código. O primeiro (`vetor` não é desalocado) já identificamos no exercíco anterior. Você consegue identificar os outros dois?

    !!! answer
        O loop de exibição imprime até a posição $N$, porém as $N$ posições do array são $0,1,\dots,N-1$.
        O mesmo erro é realizado na função `atribui`, que faz um acesso indevido `vetor[N]`.

!!! example "Vamos corrigir!"
    Corrija os erros apontados na questão anterior e salve o programa em um arquivo *ex1-certo.c*.

## Ferramentas de verificação de memória

Para poder identificar mais facilmente problemas relativos a memória, iremos utilizar uma ferramenta chamada **Valgrind**. Para saber mais sobre o valgrind acesse o link:

[https://diveintosystems.org/book/C3-C_debug/valgrind.html](https://diveintosystems.org/book/C3-C_debug/valgrind.html)

O Valgrind é um detector de má gestão de memória. Ele roda seu programa em cima de um ambiente modificado e aponta os seguintes erros:

1. memória alocada e não liberada
1. acessos (leituras e escritas) a posições de memória não alocada ou inválidas

O valgrind  está disponível na maioria das distribuições Linux modernas. Instale com:

<div class="termy">

```console
$ sudo apt update
$ sudo apt install valgrind
```





</div>

!!! tip "Dica"
    
    É recomendável manter o hábito de atualizar o Linux de tempos em tempos. Faça com:

<div class="termy">

```console
$ sudo apt update
$ sudo apt upgrade
```

</div>

Para que os problemas encontrados pelo Valgrind sejam mais facilmente identificados, iremos passar a compilar utilizando a flag `-g`.

!!! example
    Compile os programas `ex1` e `ex1-certo` criados na parte anterior incluindo também a flag `-g`.

<div class="termy">

```console
$ gcc -Og -g -Wall -std=c99 ex1.c -o ex1
$ gcc -Og -g -Wall -std=c99 ex1-certo.c -o ex1-certo
```

</div>


!!! exercise text short
    Rode o Valgrind com `valgrind --leak-check=yes ./ex1`. Quantos erros foram encontrados? Quais são seus tipos (escrita ou leitura de dados)? O que eles significam?

    !!! answer
        Iremos discutir cada um dos erros!

---------------

O primeiro erro encontrado é

```
==1899== Invalid write of size 4
==1899==    at 0x1086C7: main (ex1.c:11)
==1899==  Address 0x522f078 is 0 bytes after a block of size 56 alloc'd
==1899==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==1899==    by 0x1086B9: main (ex1.c:7)
```

!!! exercise text short
    Em qual linha o erro ocorre? O que a mensagem acima significa?

    !!! answer
        O erro ocorre na linha 11, ao escrever em vetor[i] quando `i == N`

---------

O segundo erro é

```
==1899== Invalid read of size 4
==1899==    at 0x1086DD: main (ex1.c:15)
==1899==  Address 0x522f078 is 0 bytes after a block of size 56 alloc'd
==1899==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==1899==    by 0x1086B9: main (ex1.c:7)
```

!!! exercise text short
    Em qual linha o erro ocorre? O que a mensagem acima significa?

    !!! answer
        O erro ocorre na linha 15, ao ler vetor[i] quando `i == N`.

---------

A seção *HEAP SUMMARY* faz um resumo dos dados alocados/desalocados no seu programa. A saída abaixo foi obtida ao rodar o valgrind para o exercício 1 original:

```
==2179== HEAP SUMMARY:
==2179==     in use at exit: 56 bytes in 1 blocks
==2179==   total heap usage: 2 allocs, 1 frees, 1,080 bytes allocated
==2179==
==2179== 56 bytes in 1 blocks are definitely lost in loss record 1 of 1
==2179==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==2179==    by 0x1086B9: main (ex1.c:7)
```

!!! exercise text short
    Ela mostra algum problema? Se sim, qual linha de código é apontada? Qual é o problema diagnosticado por este aviso?

    !!! answer
        Ela indica que houveram 2 `mallocs' e somente 1 `free`. Ou seja, alguma alocação de memória deixou de liberar dados. Abaixo, são indicadas em quais linhas os `malloc` sem `free` ocorreram (linha 7 na função `main`)


!!! example
    Verifique que seu programa corrigido *ex1-certo.c* roda sem erros no valgrind. Se não, corrija os problema e rode novamente até que rode sem erros.


## Implementações de funções (**Entrega**)

Os exercícios abaixo estão disponíveis no repositório de entregas (pasta `atv/08-malloc`).

!!! tip "Dica!"
    Leia o `README.md` na pasta da atividade!

!!! example "To Do"
    Abra o arquivo *copia_string.c* e implemente a função *mystrcpy*. Esta função recebe uma string, e devolve uma cópia da string original, alocando apenas o espaço realmente necessário.

!!! example "To Do"
    Abra o arquivo *concatena_string.c* e implemente a função *mystrcat*. Esta função recebe duas string, e devolve uma terceira que é a concatenação das duas primeiras, alocando apenas o espaço realmente necessário.

!!! warning "Atenção!"
    Não se esqueça de checar se sua implementação tem erros usando o valgrind.

