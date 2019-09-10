% 11 - Alocação Dinâmica de Memória
% Sistemas Hardware-Software - 2019/2
% Igor Montagner

# Parte 1 - Aquecimento

**Exercício 1:** Abra o arquivo *ex1.c* em um editor e compile-o usando as flags da disciplina (`-Og -Wall -std=c99`). **Sem rodar o programa**, responda as questões abaixo. 

**a)** Analisando seu código-fonte, o que este programa faz?  \vspace{3em}

**b)** Na execução deste programa, existe alguma possibilidade da alocação dinâmica com `malloc` falhar? Caso sim, indique as situações onde isto poderia acontecer. \vspace{3em}

**c)** O que seria necessário alterar no código para checar se `malloc` falha ou não? Efetue estas alterações. Para testar, edite o código para que sejam solicitados espaços de memória de tamanho muito grande (acima da quantidade de memória disponível). \vspace{3em}

**Exercício 2:** Execute o programa acima e responda as questões abaixo. 

**a)** Ocorreu algum problema durante a execução? \vspace{3em}

**b)** Existem três problemas no código. Você consegue identificá-los? Corrija-os e salve o programa em um arquivo *ex1-certo.c*. \vspace{3em}

# Parte 2 - Valgrind

Para poder identificar mais facilmente problemas relativos a memória, iremos utilizar uma ferramenta chamada Valgrind.

O Valgrind é um detector de má gestão de memória, ele mostra vazamentos de memória, erros de desalocação que nem sempre podem ser facilmente identificados pelo programador apenas com a análise visual do código.

Instale o Valgrind com os seguintes comandos:

`sudo apt-get update`

`sudo apt-get install valgrind`

Para que os problemas encontrados pelo Valgrind sejam mais facilmente identificados, iremos passar a compilar utilizando a flag `-g`.
\vspace{1em}

**Exercício 3:** Vamos rodar agora o programa acima usando o valgrind. 

**a)** Rode o Valgrind com `valgrind --leak-check=yes ./ex1`. Quais foram os problemas encontrados e em quais linhas do código?  \vspace{3em}

**b)** O quê significa o primeiro erro? Como corrigí-lo?  \vspace{3em}

**c)** O quê significa o segundo erro? Como corrigí-lo?  \vspace{3em}

**d)** O quê significa o terceiro erro? Como corrigí-lo?  \vspace{3em}

**e)** Verifique que seu programa corrigido *ex1-certo.c* roda sem erros no valgrind. 


# Parte 3 - implementações de funções


**Exercício 4:** Abra o arquivo *ex4.c* e implemente a função *mystrcpy*. Esta função recebe uma string, e devolve uma cópia da string original, alocando apenas o espaço realmente necessário.

**a)** Efetue alguns testes no terminal e confira se está ok. \vspace{2em}

**b)** Confira com o Valgrind se a sua implementação produz algum erro em relação aos acessos de memória. \vspace{2em}

**Exercício 5:** Abra o arquivo *ex5.c* e implemente a função *mystrcat*. Esta função recebe duas string, e devolve uma terceira que é a concatenação das duas primeiras, alocando apenas o espaço realmente necessário.

**a)** Efetue alguns testes no terminal e confira se está ok. \vspace{2em}

**b)** Confira com o Valgrind se a sua implementação produz algum erro em relação aos acessos de memória. \vspace{2em}

**Exercício 6:** Você percebeu que, no código base dos dois exercícios anteriores a memória alocada dinamicamente não foi devolvida ao sistema? Nestes casos, explique qual parte do código deve ser responsável pela liberação e por que?\vspace{5em}

# Parte 4 - implementação de programas completos

Ao finalizar os exercícios abaixo cheque se sua solução não produz erros de memória usando o *Valgrind*.

**Exercício 7:** Crie um programa para ler o preço de fechamento do dia de uma determinada ação para *n* dias. Na entrada, o primeiro valor será um inteiro *n* referente a quantidade de dias, seguido por *n* valores reais referentes ao preço de fechamento da ação em cada um dos *n* dias.
Você precisará alocar um vetor de tamanho *n* para armazenar as leituras. Após, calcule algumas estatísticas (média, máximo, mínimo e desvio padrão) e exiba estas informações. Salve este programa em um arquivo *ex7.c*.


**Exercício 8:** Refaça o programa anterior. Agora, considere que a quantidade de dias não será mais informada e o programa irá parar quando ler qualquer valor negativo. Inicialmente, efutue a alocação de um vetor de cinco posições. Cada vez que o vetor estiver cheio e for necessária uma nova posição, aloque mais cinco utilizando a função `realloc`. Ao final, exiba os valores na ordem inversa a da entrada. Salve este programa como *ex8.c*.

