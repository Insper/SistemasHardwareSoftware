# K-Nearest Neighbors Classifier

O **KNN** (k-vizinhos mais próximos) é um método de aprendizado de máquina desenvolvido em 1951 que pode ser utilizado para classificação. A ideia do **KNN** é simples: com base na hipótese de que registros com resposta semelhante possuem características semelhantes, para classificar um novo registro, o **KNN** busca encontrar os `k` vizinhos mais semelhantes ao registro que se deseja classificar, decidindo pela classe com maior frequência.

![KNN Example](knn.png)
Fonte: *http://res.cloudinary.com/dyd911kmh/image/upload/f_auto,q_auto:best/v1531424125/KNN_final1_ibdm8a.png*

Neste lab, sua tarefa será utilizar os conceitos aprendidos sobre **threads** para acelerar o processo de predição de um programa que implementa o **KNN**.

A implementação do **KNN** já está disponível (ver `knn.h` e compilar com `knn.o`). Veja um exemplo do seu uso.
```c
#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

int main(int argc, char *argv[]) {
    // Abre dataset de treinamento
    t_data *data_train = read_csv("ex_10000-size_7-classes_15-features_train.csv");    

    // Treina modelo
    t_knn_classifier *knn_model = knn_fit(data_train, 3);

    // Aloca vetor para armazenar a predição
    long *pred_train = malloc(sizeof(long) * data_train->n_rows);

    // Para cada registro (linha da matriz) de treinamento, faz a predição
    for(long i = 0; i < data_train->n_rows; i++) {
        pred_train[i] = knn_predict(knn_model, data_train->mat[i]);
    }

    // Performance do modelo em treinamento
    printf("Accuracy score train:\t%.3f\n", accuracy_score(get_target(data_train), pred_train, data_train->n_rows));

    // Abre os dados de teste
    t_data *data_test = read_csv("ex_10000-size_7-classes_15-features_test.csv");

    long *pred_test= malloc(sizeof(long) * data_test->n_rows);

    // Para cada registro (linha da matriz) de teste, faz a predição
    for(long i = 0; i < data_test->n_rows; i++) {
        pred_test[i] = knn_predict(knn_model, data_test->mat[i]);
    }

    // Performance do modelo nos dados de teste
    printf("Accuracy score test:\t%.3f\n", accuracy_score(get_target(data_test), pred_test, data_test->n_rows));

    return 0;
}
```

Perceba que esta versão de exemplo faz tudo de forma sequêncial, sem threads. Sua tarefa é melhorar este trabalho, recebendo argumentos da linha de comando e fazer as alterações necessárias para que o trabalho considere threads.

## Onde desenvolver?
Foi criado uma pasta `lab/03-knn` em seu repositório de entregas da disciplina. Crie um arquivo `classifier.c` para resolver seu lab!

Para compilar, você pode utilizar:
<div class="termy">

    ```console
    $ gcc -Wall -Wno-unused-result -g classifier.c knn.o -o classifier -lm -pthread 
    ```
</div>

!!! warning "Atenção"
    Você pode querer alterar a estrutura de seu lab, criar um makefile ou compilar de forma diferente. Considere como obrigatório informar no `README.md` da pasta `lab/03-knn` como seu programa pode ser compilado.

## Como e o que entregar?
A correção deste lab será manual (pasta ter commit, não precisa fazer tag). Deixe no `README.md` um pequeno relatório explicando como compilar e executar seu programa, detalhes de implementação, além de um vídeo de sua solução funcionando (opcional, ver rubrica A).

Quais detalhes de implementação:
- Explique brevemente (um ou dois parágrafos) como você sincronizou as threads em cada conceito
- Explique brevemente (um ou dois parágrafos) as chamadas de sistema utilizadas

### Conceito **I**

- O programa não compila
- O programa não executa


### Conceito **D**

- Implementou a rubrica C, mas o programa compila com warnings ou utiliza variáveis globais sem necessidade

### Conceito **C**

- O programa recebe os seguintes argumentos na linha de comando
    - `-k n_vizinhos`: informa o argumento do classificador, números de vizinhos a serem considerados
    - `-d path_train_csv`: informa o path para o arquivo CSV de treinamento
    - `-t path_test_csv`: informa o path para o arquivo CSV de teste
- Seu programa deve treinar o KNN (na main, pode ser sem criar nova thread)
- Seu programa deve fazer predict do KNN tanto do treino quanto do teste, mostrando a acurácia de cada um deles
- Na etapa de **predict**, o **predict** deve obrigatoriamente utilizar threads. A thread deve fazer predict de **um** registro e devolver sua classe
- Implementou a rubrica B, mas o programa compila com warnings ou utiliza variáveis globais sem necessidade


### Conceito **B**

- Modifique o conceito C para considerar que o programa receba um novo argumento na linha de comando
    - `-n n_threads`: o **predict** deve executar `n_threads` por vez.
- Implementou a rubrica A, mas o programa compila com warnings ou utiliza variáveis globais sem necessidade

### Conceito **A**

- Modifique o conceito B para criar uma janela gráfica com uma **barra de progresso** das etapas de **predict**. Após terminar, adicione à janela as informações de acurácia
- Criou vídeo de um a três minutos explicando o projeto, mostrando o programa em funcionamento

Neste conceito você pode utilizar qualquer biblioteca que considerar interessante, desde que em C. Sugiro o uso da `raylib`.

Veja um exemplo do uso dela:

```c
#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```
Para mais detalhes, acesse:
- https://github.com/raysan5/raylib
- https://www.raylib.com/index.html
- https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
