# 14 - Carregamento de programas

!!! pdf
    ![](slides.pdf)

<br>


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

Suponha que o código `exemplo-args.c` acima foi compilado para o programa `exemplo-args`. Considerando a invocação a seguir `exemplo-args teste var bla foo`, responda às perguntas abaixo **sem rodar o programa**.

!!! exercise text choice
    Qual os valores de `argc` e `argv`?

    - [ ] `argc=1, argv={"exemplo-args"}`
    - [x] `argc=5, argv={"exemplo-args", "teste", "var", "bla", "foo"}`
    - [ ] `argc=4, argv={"teste", "var", "bla", "foo"}`
    - [ ] `argc=3, argv={"teste", "var", "bla", "foo"}`

    !!! answer "Resposta"
        São 5 argumentos, contando com `argv[0]` sendo o nome do programa chamado. 

!!! exercise text short
    Qual seria a saída do programa para a invocação acima?

    !!! answer "Resposta"
        ```
        exemplo-args
        teste
        var
        bla
        foo
        ```

!!! exercise text short
    Qual o significado de `argv[0]`?

    !!! answer "Resposta"
        É o nome do programa chamado.

!!! example
    Crie um programa `soma` que tem o seguinte comportamento:

    1. Se o programa for chamado com menos de 2 argumentos mostrar mensagem de erro e sair.
    1. Se o programa for chamado com 2 ou mais argumentos, mostrar no terminal a soma deles.
    1. Se um argumento não for um número considerá-lo como 0.

    **Dica**: execute `man atof` no terminal ;)

## Carregando novos programas com `exec`

A chamada `exec` é usada para carregar programas na memória e executá-los. O novo programa é carregado no contexto do processo atual, substituindo-o por completo. Veja um exemplo de uso correto do `execvp` abaixo, o código fonte está em `exemplo-exec.c`.

```cpp
char prog[] = "ls";
// a lista de argumentos sempre começa com o nome do
// programa e termina com NULL
char *args[] = {"ls", "-l", "-a", NULL};

execvp(prog, args);
printf("Fim do exec!\n");
```

!!! exercise text choice
    Supondo que o `execvp` funcione, a linha `printf("Fim do exec!\n")` executa?

    - [ ] SIM
    - [x] NÃO

    !!! answer "Resposta"
        A linha não é executada se o `execvp` funcionar. O programa antigo é completamente substituído pelo novo programa quando o `execvp` funciona.

Os argumentos passados no `execvp` são passados para o `main` do programa executado via argumentos do `main`. Ao fazer a chamada

```cpp
char prog[] = "prog1";
char *args[] = {"prog1", "arg1", "arg2", NULL};

execvp(prog, args);
```

!!! exercise text choice
    Qual é o valor de `argc` e `argv` passado para `prog1`?

    - [ ] `argc=1, argv={"prog1"}`
    - [x] `argc=3, argv={"prog1", "arg1", "arg2"}`
    - [ ] `argc=2, argv={"arg1", "arg2"}`
    - [ ] `argc=4, argv={"prog1", "arg1", "arg2", NULL}`

    !!! answer "Resposta"
        Serão três argumentos!

!!! note "Em caso de dúvidas consulte o manual (`man`)"
    Caso tenha dúvidas, lembre-se do comando `man`. Explore o manual do `execvp` com:
    <div class="termy">

    ```console
    $ man 3 execvp
    ```

    </div>

!!! warning
    Os dois próximos exercícios você começar o programa do zero (vazio), pois adaptar exemplos anteriores, apesar de prático, atrapalha a memorização dos comandos usados.

!!! note "Executando programas fora do `PATH` do sistema"
    Nos exemplos de **exec**, supomos que os programas a serem executados estavam no **PATH** do sistema. Caso você queira subir algum executável que está na própria pasta do seu projeto (ou em qualquer caminho fixo/relativo conhecido), utilize algo como (**lembre do `./`**):

    ```C
    // Lembre de usar "./" neste caso
    char *args[] = {"./meuprograma", NULL};
    if (execvp(args[0], args) == -1) {
        perror("execvp failed!");
        exit(EXIT_FAILURE);
    }
    ```

!!! note "Várias formas de chamar `exec`"
    No manual, percebemos que temos várias chamadas de exec: `execl`, `execlp`, `execle`, `execv`, `execvp` e `execvpe`.
    Releia prestando atenção nas diferenças.
    
    Aqui, um auxílio de IA será útil! Abra o link https://chatbot.theb.ai/ e faça perguntas como:
    
    `"whats the difference between C functions execv and execvp?"`.

    Solicite exemplos e valide códigos!

!!! exercise
    Crie um programa `eh_par` que recebe um inteiro como argumento de linha de comando e cujo `main` retorne 1 se o número for par, 0 caso contrário e -1 se ele for negativo.

    **Dicas**:

    * pesquise a função `atol` para fazer a conversão do argumento de linha de comando para `long`.
    * você pode testar seu programa no terminal: basta rodar `eh_par 10` para checar se o número 10 é par.
    * para ver o valor de saída do último programa rodado execute `echo $?`
    * crie um arquivo `eh_par.c` e compile para `eh_par`


Vamos agora juntar `fork`, `wait` e `exec` em um único exercício!

!!! exercise
    Crie um programa que recebe números via `scanf`, executa `eh_par` em um processo filho e usa seu valor de retorno para decidir se o número é par ou não. Seu programa deverá parar de receber números quando `eh_par` retornar -1.

    **Dica**: você pode usar `sprintf` para converter o inteiro lido para string. Se não souber como usar consulte o manual executando `man sprintf` no terminal.
