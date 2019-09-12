% 12 - Tipos abstratos de dados
% Sistemas Hardware-Software - 2019/2
% Igor Montagner

# Parte 1 - o tipo `Point2D`

Vamos considerar primeiro uma estrutura usada para guardar um ponto 2D. Este tipo de estrutura seria útil ao trabalhar com algoritmos de Geometria Computacional.

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

A ideia de um *Tipo Abstrato de Dados* é formalizar um "contrato" que lista quais operações podem ser feitas com este dado. Estas operações são abstratas e não dependem de nenhuma implementação específica do tipo. Por exemplo, declarar o ponto com contendo um `double coords[2]` não muda os resultados de nenhuma das operações acima mas mudaria o código de acesso a coordenada `x` (`p.x` vs `p.coords[0]`). Veja um exemplo concreto de como fazer isto abaixo (arquivo *point2d.h*).

<div class="include code" id="src/point2d.h" language="c"></div>

Note que no exemplo acima não permitimos no contrato que o usuário do nosso ponto mude suas coordenadas. Mais ainda, a definição de um ponto não está nem inclusa no arquivo! Podemos declarar ponteiros para `Point2D` (pois eles são, em essência, endereços de tamanho 8 bytes) e passá-los para as funções de nosso *TAD* mas não podemos mexer nos campos internos do `Point2D`! Por isso, **alocação dinâmica de memória** é essencial em *TAD*s: ela permite que todos os detalhes da implementação interna estejam **encapsulados** e que só possamos interagir com o tipo via as funções definidas para isso.

**Exercício 1**: Abra o arquivo `teste_point2d.c`. Você consegue entender seu conteúdo? 

**Exercício 2**: Compile o arquivo `teste_point2d.c` usando a seguinte linha de comando. Rode-o logo em seguida. O que significa sua saída?

> `$ gcc -Og -Wall -g teste_point2d.c point2d.c -o teste_ponto`

**Exercício 3**: Abra o arquivo `point2d.c` e complete as partes faltantes. Verifique se tudo funciona corretamente usando `teste_point2d.c`. Você deve aproveitar ao máximo as funções já criadas (ou seja, pode usar `point2d_new` nas outras funções).

**Entrega**: agora que sua implementação do *TAD* `Point2D` está completa, compile o arquivo `teste_point2d.c` e execute-o usando o *Valgrind*. Se seu programa rodar sem erros, entregue-o no Blackboard. 

**Exercício 4:** Os testes escritos em `teste_point2d.c` lembram código escrito em linguagens de mais alto nível, como Java. Uma grande diferença é que toda função começa com `point2D_`. Pesquise por que isto é necessário e explique abaixo.

# Parte 2 - entrega

Você deverá entregar, até **20/09** o arquivo completo *point2d.c* e o **exercício 8** da aula 11. Ambos programas deverão rodar sem erros no `valgrind`.
