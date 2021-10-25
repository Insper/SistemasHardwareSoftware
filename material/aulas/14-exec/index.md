# 14 - Carregamento de programas

## Argumentos de um programa

Leia com atenção o código antes de responder os próximos exercícios.

```cpp
int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("arg: %s\n", argv[i]);
    }

    return 0;
}
```

O código acima foi compilado para o programa `exemplo-args`. Considerando a invocação a seguir `exemplo-args teste var bla foo`, responda às perguntas abaixo **sem rodar o programa**.

!!! question choice
    Qual os valores de `argc` e `argv`?

    - [ ] `argc=1, argv={"exemplo-args"}`
    - [x] `argc=5, argv={"exemplo-args", "teste", "var", "bla", "foo"}`
    - [ ] `argc=4, argv={"teste", "var", "bla", "foo"}`
    - [ ] `argc=3, argv={"teste", "var", "bla", "foo"}`

    !!! details "Resposta"
        São 5 argumentos, contando com `argv[0]` sendo o nome do programa chamado. 

!!! question short
    Qual seria a saída do programa para a invocação acima?

    !!! details "Resposta"
        ```
        exemplo-args
        teste
        var
        bla
        foo
        ```

!!! question short
    Qual o significado de `argv[0]`?

    !!!! details "Resposta"
        É o nome do programa chamado.

!!! example
    Crie um programa `soma` que tem o seguinte comportamento:

    1. Se o programa for chamado com menos de 2 argumentos mostrar mensagem de erro e sair.
    1. Se o programa for chamado com 2 ou mais argumentos, mostrar no terminal a soma deles.
    1. Se um argumento não for um número considerá-lo como 0.

    **Dica**: execute `man atof` ;)

## Carregando novos programas com `exec`

A chamada `exec` é usada para carregar programas na memória e executá-los. O novo programa é carregado no contexto do processo atual, substituindo-o por completo. Veja um exemplo de uso correto do `execvp` abaixo.

```cpp
char prog[] = "ls";
// a lista de argumentos sempre começa com o nome do
// programa e termina com NULL
char *args[] = {"ls", "-l", "-a", NULL};

execvp(prog, args);
printf("Fim do exec!\n");
```

!!! question choice
    Supondo que o `execvp` funcione, a linha `printf("Fim do exec!\n")` executa?

    - [ ] SIM
    - [x] NÃO

    !!! details "Resposta"
        A linha não é executada se o `execvp` funcionar. O programa antigo é completamente substituído pelo novo programa quando o `execvp` funciona.

Os argumentos passados no `execvp` são passados para o `main` do programa executado via argumentos do `main`. Ao fazer a chamada

```cpp
char prog[] = "prog1";
char *args[] = {"prog1", "arg1", "arg2", NULL};

execvp(prog, args);
```

!!! question choice
    Qual é o valor de `argc` e `argv` passado para `prog1`?

    - [ ] `argc=1, argv={"prog1"}`
    - [x] `argc=3, argv={"prog1", "arg1", "arg2"}`
    - [ ] `argc=2, argv={"arg1", "arg2"}`
    - [ ] `argc=4, argv={"prog1", "arg1", "arg2", NULL}`

!!! warning
    Faça os dois programas abaixo do zero. Adaptar exemplos anteriores, apesar de prático, evita que repitamos os comandos e isto atrapalha a memorização dos comandos usados.

!!! example
    Crie um programa `eh_par` que recebe um inteiro como argumento de linha de comando e cujo `main` retorne 1 se o número for par, 0 caso contrário e -1 se ele for negativo.

    **Dicas**:

    * pesquise a função `atol` para fazer a conversão do argumento de linha de comando para `long`.
    * você pode testar seu programa no terminal: basta rodar `eh_par 10` para checar se o número 10 é par.
    * para ver o valor de saída do último programa rodado execute `echo $?`


Vamos agora juntar `fork`, `wait` e `exec` em um único exercício!

!!! example
    Crie um programa que recebe números via `scanf`, executa `eh_par` em um processo filho e usa seu valor de retorno para decidir se o número é par ou não. Seu programa deverá parar de receber números quando `eh_par` retornar -1.

    **Dica**: você pode usar `sprintf` para converter o inteiro lido para string. Se não souber como usar consulte o manual.


