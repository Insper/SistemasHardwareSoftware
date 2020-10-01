# 10 - Alocação Dinâmica de Memória

## Exercícios básicos

!!! example
    Abra o arquivo *ex1.c* em um editor e compile-o usando as flags da disciplina (`-Og -Wall -std=c99`).

**Sem rodar o programa**, responda as questões abaixo.

!!! question short
    Analisando seu código-fonte, o que este programa faz?

!!! question short
    Na execução deste programa, existe alguma possibilidade da alocação dinâmica com `malloc` falhar? Caso sim, indique as situações onde isto poderia acontecer.

!!! question short
    O seu programa libera toda memória que aloca? Se não, aponte onde ele deveria fazer isto.

------

Agora execute o programa acima e responda as questões abaixo.

!!! question short
    Ocorreu algum problema durante a execução?

!!! question short
    O comportamento de seu programa muda conforme N? Vá incrementando de um em um e veja o que acontece. Você consegue explicar por que? Discuta com seu grupo e valide sua resposta com o professor.

!!! question short
    Existem três problemas no código. O primeiro (`vetor` não é desalocado) já indetificamos no exercíco anterior. Você consegue identificar os outros dois? Corrija-os e salve o programa em um arquivo *ex1-certo.c*.

## Ferramentas de verificação de memória

Para poder identificar mais facilmente problemas relativos a memória, iremos utilizar uma ferramenta chamada Valgrind.

O Valgrind é um detector de má gestão de memória. Ele roda seu programa em cima de um ambiente modificado e aponta os seguintes erros:

1. memória alocada e não liberada
1. acessos (leituras e escritas) a posições de memória não alocada ou inválidas

O valgrind  está disponível na maioria das distribuições Linux modernas

```
sudo apt-get install valgrind
```

Para que os problemas encontrados pelo Valgrind sejam mais facilmente identificados, iremos passar a compilar utilizando a flag `-g`.

!!! example
    Compile os programas `ex1` e `ex1-certo` criados na parte anterior com a flag `-g`.

!!! question medium
    Rode o Valgrind com `valgrind --leak-check=yes ./ex1`. Quais foram os problemas encontrados e em quais linhas do código?

!!! question short
    O quê significa o primeiro erro? Como corrigí-lo?

!!! question short
    O quê significa o segundo erro? Como corrigí-lo?

!!! question short
    A seção *HEAP SUMMARY* faz um resumo dos dados alocados/desalocados no seu programa. Ela mostra algum problema? Se sim, qual linha de código é apontada? Qual é o problema diagnosticado por este aviso?

!!! example
    Verifique que seu programa corrigido *ex1-certo.c* roda sem erros no valgrind. Se não, corrija os problema e rode novamente até que rode sem erros.


## Implementações de funções (**Entrega**)

Os exercícios abaixo estão disponíveis no repositório de entregas (pasta `08-malloc`).

!!! example
    Abra o arquivo *ex4.c* e implemente a função *mystrcpy*. Esta função recebe uma string, e devolve uma cópia da string original, alocando apenas o espaço realmente necessário.

!!! example
    Abra o arquivo *ex5.c* e implemente a função *mystrcat*. Esta função recebe duas string, e devolve uma terceira que é a concatenação das duas primeiras, alocando apenas o espaço realmente necessário.

!!! warning
    Não se esqueça de checar se sua implementação tem erros usando o valgrind.

