% 12 - Tipos abstratos de dados
% Sistemas Hardware-Software - 2020/1
% Igor Montagner

# Parte 1 - revisando TADs

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

<div class="include code" id="src/point2d.h" language="c"></div>

### Ponteiros opacos

Note que no exemplo acima a definição do `struct` `Point2D` não está inclusa no arquivo `point2d.h`! Por conta de ponteiro se um tipo de dado em *C*, podemos declarar ponteiros para `Point2D` e passá-los para as funções de nosso *TAD* *mesmo sem saber a definição exata de onde eles apontam!*. Só não podemos tentar acessar *a variável apontada* por este ponteiros (usando `*` ou `->`). Por isso, **alocação dinâmica de memória** é essencial em *TAD*s: ela permite que todos os detalhes da implementação interna estejam **encapsulados** e que só possamos interagir com o tipo via as funções definidas para isso.

**Exercício 1**: Abra o arquivo `teste_point2d.c`. Você consegue entender seu conteúdo?

**Exercício 2**: Compile o arquivo `teste_point2d.c` usando a seguinte linha de comando. Rode-o logo em seguida. O que significa sua saída?

> `$ gcc -Og -Wall -g teste_point2d.c point2d.c -o teste_ponto`

**Exercício 3**: Abra o arquivo `point2d.c` e complete as partes faltantes. Verifique se tudo funciona corretamente usando `teste_point2d.c`. Você deve aproveitar ao máximo as funções já criadas (ou seja, pode usar `point2d_new` nas outras funções).

**Entrega**: agora que sua implementação do *TAD* `Point2D` está completa, compile o arquivo `teste_point2d.c` e execute-o usando o *Valgrind*. Se seu programa rodar sem erros, entregue-o no Blackboard.

# Parte 2 - vetores dinâmicos

Agora que já vimos vetores dinâmicos em aula, vamos implementá-los. Nosso vetor tem a seguinte interface:

<div class="include code" id="src/vec_int.h" language="c"></div>

**Entrega**: implemente a estrutura *vetor dinâmico* no arquivo *vec_int.c* e compile o programa de testes da mesma maneira que foi feito na parte anterior. Para sua entrega estar 100% seu programa de testes deverá rodar sem erros no *valgrind*.


