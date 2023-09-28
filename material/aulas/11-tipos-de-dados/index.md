# 11 - Tipos abstratos de dados

## A estrutura `Point2D`

Vamos considerar primeiro uma estrutura usada para guardar um ponto 2D. Este tipo de estrutura seria útil ao trabalhar com algoritmos de Geometria Computacional ou mesmo em aplicações de física.

~~~{.C}
typedef struct {
    double x, y;
} Point2D;
~~~

Vamos listar algumas operações que podem ser feitas com um ponto:

1. Inicialização e finalização - todo ponto deve ser inicializado com algum valor para x e y.
1. Somar dois pontos (e obter um terceiro);
1. Calcular o coeficiente angular de uma reta que passe pelos dois pontos;
1. Multiplicar ambas as coordenadas de um ponto (recebendo um novo em troca) - esta operação equivale a mudanças de escala
1. Retornar os valores das componentes x e y do ponto;

A ideia de um *Tipo Abstrato de Dados* é formalizar um "contrato" que lista quais operações podem ser feitas com este dado. Estas operações não dependem de nenhuma implementação em particular do tipo. Por exemplo, declarar o ponto com contendo um `double coords[2]` não muda os resultados de nenhuma das operações acima mas mudaria o código de acesso a coordenada `x` (`p.x` vs `p.coords[0]`). Veja um exemplo concreto de como fazer isto abaixo (arquivo *point2d.h*).

```c
#ifndef __POINT2D__
#define __POINT2D__

typedef struct{
    double x, y;
}Point2D;

Point2D *point2D_new(double x, double y);
void point2D_destroy(Point2D *p);

double point2D_get_x(Point2D *p);
double point2D_get_y(Point2D *p);

Point2D *point2D_add(Point2D *p1, Point2D *p2);
double point2D_theta(Point2D *p1, Point2D *p2);
Point2D *point2D_scale(Point2D *p, double s);

#endif
```

!!! tip
    Em *C* declaramos os **tipos abstratos de dados** e as **funções**  que podem ser usadas por outras partes do código em arquivos `.h` e implementamos essas funções em arquivos `.c` (de mesmo nome, muitas vezes). Assim conseguimos organizar nosso código em vários módulos e depois juntá-los no momento da compilação. 

Notem que essa lista de operações "toma conta" da alocação e liberação de memória. Ou seja, o usuário de nosso `Point2D` não precisa se preocupar com malloc ou free. Basta que ele chame nossas funções.

!!! tip "Por que todas as funções começam com `point2D_`?"
    Em *C* não existe o conceito de módulo, namespace ou qualquer outro tipo de mecanismo de importar código. Toda função, a princípio, é declarada no escopo global de nomes. Isso significa que se nomeássemos `point2D_add` simplesmente como `add` nenhuma outra função escrita, por nós ou de nenhuma outra biblioteca usada no nosso programa, poderia ter esse nome.

    A estratégia usada nesse caso, é usar um prefixo que indique a qual biblioteca a função pertence. No nosso caso, usamos `point2D_` em todas as funções para evitar colisões de nomes. 
    

## Acessando as informações do Tipo Abstrato de Dados

Note que na declaração das funções, algumas retornam um ponteiro para o Tipo Abstrato de Dados `Point2D` ou recebem como parâmetro um ponteiro para esse tipo, em ambos os casos o ponteiro foi **alocado dinamicamente na memória**. Para acessar as variáveis do tipo `Point2D`  (`x` ou `y`) devemos usar o operador `->`. Por exemplo se temos uma variável `Point2D *p`, o acesso à `x` deve ser da seguinte forma `p->x`.

!!! example
    Abra o arquivo `test_point2d.c`. Você consegue entender seu conteúdo? Examine o código e entenda como `Point2D` deve ser usado.

!!! exercise text short
    Compile o arquivo `test_point2d.c` usando a seguinte linha de comando. Rode-o logo em seguida. O que significa sua saída?

    <div class="termy">

    ```console
    $ gcc -Og -Wall -g test_point2d.c point2d.c -o teste_ponto
    ```

    </div>


    Responda aqui:
    !!! answer
        São realizadas chamadas de testes automáticos que tentam utilizar as funcionalidade de `Point2D`. Os testes falham porque as implementações não foram realizadas.

!!! example
    Abra o arquivo `point2d.c` e complete as partes faltantes. Verifique se tudo funciona corretamente usando `test_point2d.c`. Você deve aproveitar ao máximo as funções já criadas (ou seja, pode usar `point2d_new` nas outras funções).

!!! example
    Agora que sua implementação do *TAD* `Point2D` está completa, compile o arquivo `test_point2d.c` e execute-o usando o *Valgrind*. Seu programa deverá rodar sem erros.

## Vetores dinâmicos

!!! warning "Atividade para Entrega"
    Os arquivos estão na pasta `09-tad` do repositório de entregas.

!!! tip "Dica!"
    Não se esqueça de ler o `README.md` dentro da pasta `09-tad`!

Agora que já vimos vetores dinâmicos em aula, vamos implementá-los. Nosso vetor tem a seguinte interface:

```c
#ifndef __VECINT_H__
#define __VECINT_H__

typedef struct{
    int *data;
    int size;
    int capacity;
}vec_int;

vec_int *vec_int_create();
void vec_int_destroy(vec_int **v);

int vec_int_size(vec_int *v);

/* As seguinte operações devolvem
 * 1 se pos é uma posição válida e a operação foi bem sucedida
 * 0 caso contrário
 *
 * No caso de at, o valor é retornado na variável apontada por vi.
 */
int vec_int_at(vec_int *v, int pos, int *vi);
int vec_int_insert(vec_int *v, int pos, int val);
int vec_int_remove(vec_int *v, int pos);

#endif
```

!!! example
    **Entrega**: implemente a estrutura *vetor dinâmico* no arquivo *vec_int.c* e compile o programa de forma semelhante como foi feito na parte anterior. Para sua entrega estar 100% seu programa de testes deverá rodar sem erros no *valgrind*.

!!! tip "Dica!"
    Leia os testes para entender as operações realizadas e os resultados esperados!
