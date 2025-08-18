# Dicas e links

## Referência para as instruções do Assembly x86 e amd64

Este guia de referência [https://www.felixcloutier.com/x86/](https://www.felixcloutier.com/x86/) sobre as intruções da linguagem Assembly é um resumo da referência oficial da [Intel](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html). 

Acredito que para nossos propositos na disciplina de SisHard seja suficiente.

## GDB - referência completa

O GNU Debugger, mais conhecido por GDB, é um depurador do GNU. Ele pode ser usado para depuração em sistemas Unix-like, como por exemplo o Ubuntu 22.04, na nossa disciplina usaremos o GDB para entender os códigos em assemblye de atividades e do Lab01

Para aprender como depurar código com GDB acesse este link [https://diveintosystems.org/book/C3-C_debug/gdb.html](https://diveintosystems.org/book/C3-C_debug/gdb.html) e nesse link [https://diveintosystems.org/book/C3-C_debug/gdb_commands.html](https://diveintosystems.org/book/C3-C_debug/gdb_commands.html) você poderá conhecer o os principais comandos do gdb.
 
Nesse link [https://sourceware.org/gdb/current/onlinedocs/gdb](https://sourceware.org/gdb/current/onlinedocs/gdb) 
 você terá a documentação completa do GDB.

Aqui [https://sourceware.org/gdb/current/onlinedocs/gdb.html/Memory.html](https://sourceware.org/gdb/current/onlinedocs/gdb.html/Memory.html) tem as explicações do comando `x` (`x/nfu addr`) que permite examinar a memória de um programa Assembly.



## Compiler Explorer - godbolt.org

Compiler Explorer, também chamado de godbolt.org, é um site interativo de exploração de compiladores. Ele permite ao usuário inserir código em uma das linguagens C e visualizar a tradução do código para Assembly. 

Para utilizá-lo [acesse o LINK](https://godbolt.org/), a configuação do godbolt está nos slides da aula [04 - Funções-mov](https://insper.github.io/SistemasHardwareSoftware/aulas/04-funcoes-mov/slides.pdf).


## Resumo SisHard da Universidade Stanford

No link abaixo está uma visão geral dos assuntos abordados na primeira parte da disciplina de Sistemas Hardware-Software elaborado na Universidade de Stanford. 

[acesse o LINK](https://web.stanford.edu/class/cs107/guide/x86-64.html)

## Dicas ponteiros e alocação de memória na Linguagem C

Alguns links que podem ajuda-los a entender ponteiros e alocação de memória na Linguagem C.

Os links abaixo são do material desenvolvido pelo professor Paulo Feofiloff:

* [Endereços e ponteiros](https://www.ime.usp.br/~pf/algoritmos/aulas/pont.html)
* [Alocação dinâmica de memória](https://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html)

Os links abaixo são do material desenvolvido pelo professor Carlos Maziero:

* [Ponteiros](https://wiki.inf.ufpr.br/maziero/doku.php?id=c:ponteiros)
* [Alocação de memória](https://wiki.inf.ufpr.br/maziero/doku.php?id=c:alocacao_de_memoria)
* [Alocação dinâmica de matrizes](https://wiki.inf.ufpr.br/maziero/doku.php?id=c:alocacao_dinamica_de_matrizes)

Dicas do livro [Dive Into Systems](https://diveintosystems.org/book/):

* [Ponteiros](https://diveintosystems.org/book/C2-C_depth/pointers.html) e [funções com referências](https://diveintosystems.org/book/C2-C_depth/pointers_functions.html)

* [Alocação de memória](https://diveintosystems.org/book/C2-C_depth/dynamic_memory.html)

* [Alocação dinâmica de matrizes](https://diveintosystems.org/book/C2-C_depth/arrays.html)