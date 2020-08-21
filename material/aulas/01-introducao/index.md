# 01 e 02 - Exercícios de C

O início do nosso curso será uma revisão de programação em *C*. Fluência nessa linguagem é importante tanto para a primeira parte, em que examinamos como código é transformado em instruções de máquina, quanto na segunda, em que usamos *C* para interagir com o sistema operacional. 

!!! warning "Importante"
    Os exercícios desta página são complementares ao material do [Mutirão C](https://insper.github.io/Labs-de-C/). Pode ser uma boa revisitar o material do semestre passado para se recordar da estrutura básica de um programa em *C* e para as explicações detalhadas de cada funcionalidade usada nos exercícios. 

Os exercícios para entrega nesta página contarão na nota de atividades assim como os do restante do curso.

!!! example
    Faça um programa que receba dois inteiros e mostre sua divisão inteira, seu resto e sua divisão fracionária (com até 4 casas decimais). Se o segundo número for 0, seu programa deverá mostrar três 0 na saída. 

    **Entrada**
    ```
    2 3
    ```

    **Saída**
    ```
    0 2 0.6667
    ```

!!! example
    Faça um programa que mostra os dígitos de um número ao contrário. **Dica**: use o operador resto da divisão `%`.

    **Entrada**
    ```
    123456
    ```

    **Saída**
    ```
    6 5 4 3 2 1
    ```

!!! example
    Faça um programa que lê um inteiro `n` e depois `n` inteiros e computa sua média.

    **Entrada**
    ```
    4
    1
    2
    3
    4
    ```

    **Saída**
    ```
    2.5
    ```

!!! example
    **Entrega**: Faça um programa que lê um inteiro `n` e mostre os `n` primeiros números da tabuada para todos os números entre `2` e `n`.

    **Entrada**
    ```
    4
    ```

    **Saída**
    ```
    2 4 6 8
    3 6 9 12
    4 8 12 16
    ```

!!! example
    Faça um programa que lê três inteiros `n`, `d1` e `d2` e imprime todos os inteiros entre `2` e `n` que são divisíveis ao mesmo tempo por `d1` e `d2`.

    **Entrada**
    ```
    15 3 2
    ```

    **Saída**
    ```
    6 12 
    ```

!!! example
    Faça um programa que lê até `100` inteiros e os guarda em um vetor global `nums`. Você deve parar de ler inteiros ao receber um inteiro negativo, que não deverá ser guardado. Depois de armazená-los, leia um um número `d` e imprima na tela quantos números lidos são maiores que `d`.

    **Entrada**:
    ```
    1
    2
    3
    4
    -1
    3
    ```

    **Saída**
    ```
    1
    ```

!!! example
    Faça um programa que lê uma linha de texto e mostra no terminal seu tamanho. 

    **Entrada**:
    ```
    abcdefgh
    ```

    **Saída**
    ```
    8
    ```    

!!! example
    Faça um programa que lê uma linha de texto e conta quantas palavras tem na linha. Todo caractere não alfanumérico divide uma palavra. Veja o exemplo abaixo.

    **Entrada**:
    ```
    palavra dois tres,quatro1continua. Cinco     3seis#sete
    ```

    **Saída**
    ```
    7
    ```

!!! example
    **Entrega**: Faça uma função que determina se uma string é igual se lida de trás para frente. Você deverá ignorar todos os caracteres não alfanuméricos. 

    **Dica**:
    
    1. Se necessário, consulte novamente a [seçao de Strings](https://insper.github.io/Labs-de-C/Lab4/#strings) do Mutirão. 
    2. Como você checaria todos os caracteres entre '0' e '9'? E para as letras maiúsculas e minúsculas? Você pode precisar consultar a Tabela ASCII para entender melhor como fazer isso. 

    **Entrada**:
    ```
    igual a laugi
    ```

    **Saída**
    ```
    SIM
    ```

!!! example
    Faça um programa que lê dois inteiros `m < 100` e `n < 100`. Então seu programa deverá ler uma matriz de `m` linhas por `n` colunas e mostrar no terminal o índice do maior valor de cada coluna.

    !!! warning "Declare sua matriz como variável global. Iremos aprender como alocar matrizes de tamanho arbitrário no curso.

    **Entrada**:    
    ```
    3 4
    1 2 5.8 6 
    3 6 9 8
    5 2 3 2.0
    ```

    **Saída**
    ```
    2 1 1 0
    ```

