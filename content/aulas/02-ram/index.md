# 02 - Representação de dados em RAM

!!! pdf
    ![](slides.pdf)

## Experimentos

Vamos trabalhar com os arquivos `experimento0-4.c`. Compile e execute cada um deles, execute e analise suas saídas. Comente os resultados comparando os valores das constantes no código em *C* e a saída dos programas. Tente entender o que está acontecendo.

Para compilar cada `.c`, utilize:

<div class="termy">

```console
$ gcc -Wall -pedantic experimento0.c -o e0
```
<br>
</div>

!!! exercise text long
    Examine o código *C* do arquivo *experimento0.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.

    !!! answer
        No exercício é definido uma `union`, que se parece com uma `struct`, 
        mas os campos compartilham o mesmo espaço de memória. Ou seja os campos 
        `variavel.num` e `variavel.letra` ocupam o mesmo endereço, e a estrutura
        ocupa 4 bytes, o tamanho do maior campo (char 1 byte e int 4 bytes).
        
        ```console
        char_ou_int variavel;
        variavel.num = 130;
        ```
        
        acima é atribuído o valor 130 os campos, mas quando é impresso o tipo char `printf("%c\n", variavel.letra);`,
        o valor 130 (0x82 em hexadecimal) não é ASCII imprimível padrão, então pode sair como um símbolo estranho (ou nada visível).

        Na saída do print `printf("%#08x\n", variavel.letra);` (print no formato hexadecimal) é impresso o valor `0xffffff82`
        pois como o campo `variavel.letra` é do tipo char (signed), temos que `130`=`0x82` (unsigned) e 
        `-126`= `0xffffff82` (unsigned).


!!! exercise text long
    Examine o código *C* do arquivo *experimento1.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.
    
    !!! answer
        Os números do *experimento1.c*  são inicializados na notação hexadecimal (por exemplo `int num1 = 0x0a0c0b0d;`).
        Na memória os bytes da variável `num1` são armazenados do byte menos significativo para o mais significativo, 
        ou seja, `0d0b0c0a`. Isso mostra que a arquitetura do seu processador é **little-endian** (x86-64).


!!! exercise text long
    Examine o código *C* do arquivo *experimento2.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.
    
    !!! answer
        No exercício é declarado um array de `short` com 3 elementos, cada elemento com 2 bytes. Note que na saída a ordem dos elementos no array é preservada, mas cada short individual é armazenado em **little-endian** -- LSB (byte menos significativo) primeiro.
        
        declaração: `short arr[] = {0x1122, 0x3344, 0x5566};`
        
        saída: `22 11 44 33 66 55`

!!! exercise text long
    Examine o código *C* do arquivo *experimento3.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.
    
    !!! answer
        Nesse exercício é declarado uma *string* na linguagem C 
        
        `char *string = "Oi C :-)";`
        
        essa *string* ocupa ocupa 8 caracteres visíveis + 1 terminador `\0` = 9 bytes. Na saída são impressos
        os caracteres e seu código ASCII em hexadecimal.

        `'O'(4f) 'i'(69) ' '(20) 'C'(43) ' '(20)  ':'(3a) '-'(2d) ')'(29) ''(00)`

!!! exercise text long
    Examine o código *C* do arquivo *experimento4.c* e compare com o resultado de sua execução. Há algo estranho? Se sim, escreva abaixo algumas hipóteses para o comportamento do programa.

    !!! answer
        No trecho:
        
        ```
        int a = 10;
        int *ap = &a;
        ```

        a varível ponteiro `ap` aponta para o endereço da variável `a`, quando é feito `ap + 1`, o compilador 
        não soma 1, é somado o `sizeof(int) = 4 bytes`.

        O trecho abaixo funciona de forma análoga, 
        
        considerando que `sizeof(long) = 8 bytes`

        ```
        long l = 10;
        long *lp = &l;
        ```

## Representação de `struct` em *RAM*

A utilização de `struct` junta tudo que já vimos sobre representação de todos os tipos de dados na memória. Não se esqueça de levar em conta as questões de alinhamento mostradas na parte expositiva da aula.


!!! warning "Atenção!"
    Você **não** deverá abrir o código de `parte1.c`. Ele está no repositório para você poder conferir suas respostas.


!!! example "Vamos compilar?!"
    Compile e execute _parte1.c_.


!!! exercise text long
    Os endereços mostrados na saída de `parte1` pertencem a um só struct declarado como `struct player one`. Quais são os tamanhos de cada campo?

    **Dica**: pode não ser possível identificar *exatamente* o tamanho de cada campo, mas é esperado que você identifique ao menos o tamanho **máximo** de cada um.

    !!! answer
        No exemplo não é possível identificar o tamanho “real” de cada campo na memória por causa do alinhamento de tipos na memória, mas podemos identificar o tamanho máximo ocupado pelos endereços dos campos consecutivos, por exemplo:

        Campo `icon_id`

        Endereço: `0x596b2fdac020`

        Próximo campo (`level`) começa em `0x596b2fdac028`

        Diferença: 0x28 - 0x20 = 0x8 = 8 bytes
        

!!! exercise text short
    A segunda parte da saída de `parte1` mostra os endereços de cada campo do struct. Note que `&one` e ` &one.icon` são iguais. Você consegue explicar por que? Se não, volte na aula expositiva e reveja a parte sobre `struct` e alinhamento de memória.

    !!! answer
        Em C, um `struct` é armazenado como um bloco contíguo de memória. O primeiro campo sempre começa exatamente 
        no início do bloco que representa a `struct`, assim:

        ```
        &one        = 0x596b2fdac020
        &one.icon   = 0x596b2fdac020
        ```

!!! exercise text long
    Baseado nas respostas acima, declare abaixo o `struct`. Escreva-o da mesma maneira que usaria em um programa em *C*.

    !!! answer
        ```
        struct player {
            char icon_id;      // 1 byte
            long level;        // 8 bytes (em sistemas 64 bits)
            char name[20];     // 20 bytes
            long score;        // 8 bytes
        };
        ```

!!! example "Hora de conferir!"
    Agora confira suas respostas no arquivo _parte1.c_.

## Examinando a execução de programas usando `gdb`

Podemos examinar um programa durante sua execução usando o *gdb*. Podemos parar em qualquer instrução do programa, examinar conteúdo de registradores e da memória e listar todos os símbolos disponíveis (que podem ser funções ou variáveis globais).

!!! tip "Dica!"
    Para compilar um programa com suporte a *debugging* usamos a flag `-g` do `gcc`



<div class="termy">

```console
$ gcc -g -Wall -pedantic parte2.c -o parte2
```

</div>


Siga os passos para para carregar um programa usando o *gdb*:

1. Lance o `gdb` e passe para ele seu programa:

    <div class="termy">

    ```console
    $ gdb ./parte2
    ```

    </div>

2. Para sair, utilize:

    <div class="termy">

    ```console
    (gdb) quit
    ```

    </div>

<!-- 2. Isto nos colocará em um prompt esperando comandos. Para **rodar** o programa até o fim execute

    <div class="termy">

    ```console
    (gdb) run
    ```

    </div>


3. Após rodar, saia do gdb (utilize `quit` para sair) e abra-o novamente com o executável `parte2` **mas não faça** `run`:

    <div class="termy">

    ```console
    (gdb) quit
    $ gdb ./parte2
    ```

    </div> -->

!!! tip
    O [*gdb*](https://diveintosystems.org/book/C3-C_debug/gdb.html) é uma ferramenta poderosa que possui muitas opções. Sua documentação está online e pode ser acessada em:
    [https://sourceware.org/gdb/onlinedocs/gdb/index.html#Top](https://sourceware.org/gdb/onlinedocs/gdb/index.html#Top).

    Uma explicação detalhadas dos comandos do *gdb* pode ser encontrada nesse link:
    [https://diveintosystems.org/book/C3-C_debug/gdb_commands.html](https://diveintosystems.org/book/C3-C_debug/gdb_commands.html).

Nesta primeira parte iremos abrir o arquivo *parte2.c* e olhar seu conteúdo. Também executaremos o programa compilado *parte2*.

!!! exercise text long
    Abra o código *parte2.c* e liste os nomes das variáveis globais declaradas e seus tamanhos. Anote também as funções declaradas.


!!! warning "Atenção, tarefa dupla!"
    Para os próximos exercícios, compile o arquivo `parte2.c` **com** e **sem debugging** e repita cada exercício com ambas as versões do executável. Exemplo de compilação:

<div class="termy">

```console
$ gcc -g -Wall -pedantic parte2.c -o parte2_debug
$ gcc -Wall -pedantic parte2.c -o parte2_semdebug
```
<br>

</div>

!!! exercise text
    O comando *info* mostra informações que podem ser obtidas a partir de um executável. Execute-o e veja o que acontece.

!!! exercise
    Use `info` para mostrar as **funções** - `(gdb) info functions` e **variáveis globais** `(gdb) info variables` que existem em `parte2`. Lembre de fazer tanto na versão **com** quanto na **sem debugging**!

!!! warning "Muita informação!"
    Muitos nomes são estranhos. Eles fazem parte do padrão de arquivos executáveis *ELF*, que contém informações específicas do sistema operacional usado. Você não precisa se preocupar com estes nomes.

!!! exercise text short
    Qual é o significado da primeira coluna do comando *info variables*?

    **Dica**: o valor está em hexadecimal, que usamos na expositiva para mostrar ponteiros.
    
    !!! answer
        A primeira coluna do comando info variables no GDB mostra os endereços de memória onde as variáveis estão armazenadas na seção .data`.

!!! exercise text short
    Podemos usar o comando *print* para mostrar o valor inicial das variáveis globais identificadas. Mostre o valor inicial de `global_var` usando este comando e compare com o visto no arquivo *parte2.c*.

    **Dicas:**

    * Pode não funcionar de primeira. O quê a mensagem de erro diz?
    * A sintaxe de conversão de tipos de *C* (*casting*) pode ser útil aqui.
    
    !!! answer
        Para o executável sem degub `parte2_semdebug` use:
        
        ```
        (gdb) print (long) global_var
        $1 = 137438953472
        ```

        Para o executável com degub `parte2_debug` use:
        
        ```
        (gdb) print global_var
        $1 = 137438953472
        ```

!!! exercise text short
    Podemos usar o *gdb* também para **examinar a memória** de um executável. Acesse esta [página da documentação](https://sourceware.org/gdb/onlinedocs/gdb/Memory.html), entenda como usar o comando `x` e escreva abaixo qual o comando usado para mostrar o conteúdo do segundo item do vetor `global_array`. Em seguida, teste-o e garanta que funcionou corretamente.

    Link: https://sourceware.org/gdb/onlinedocs/gdb/Memory.html

    **Dicas**:

    1. volte nos exercícios anteriores e encontre o endereço do início do vetor
    2. calcule o endereço do segundo elemento manualmente e passe para o comando `x`
    3. não se esqueça de buscar na memória o tamanho correto do elemento

    !!! answer
        De forma geral, o comando `x` aceita até três argumentos de formatação 
        
        ```
        x/nfu endereço_de_memória
        ```
        n: o número de repetições (um valor inteiro positivo)

        f: o formato de exibição
        exemplos: s = string, i = instrução, x = hexadecimal, d = decimal, t = binário, a = endereço, etc.

        u: a unidade de exibição (quantos bytes cada item ocupa)
        exemplos: b = byte (1 byte), h = 2 bytes, w = 4 bytes, g = 8 bytes

        Considerando que o endereço da varíavel `global_array` seja  `0x0000000000004010` teríamos o comando:

        ```
        (gdb) x/1dh 0x0000000000004012
        0x4012 <global_array+2>:        10
        ```

!!! exercise text long
    `global_array` tem tipo `short`. Ou seja, é formado por dois bytes. Mostre agora o conteúdo de cada um deles. Ou seja, você deverá dar dois comandos para examinar a memória. Explique como converter esses dois bytes para o valor mostrado no exercício anterior.

    !!! answer
        Supondo que você queira ver o primeiro elemento de `global_array`:

        ```
        x/xb (char*)&global_array
        ```

        Segundo byte:

        ```
        x/xb (char*)&global_array+1
        ```

        Para ver todos os elementos:
        
        ```
        x/10xb (char*)&global_array
        ```

        

!!! exercise text short
    Use agora o comando `x` para exibir `global_str` como uma *string*. Escreva o comando abaixo.

    !!! answer

        Como a variável `global_str` é um ponteiro para uma string `char *`, o primeiro passo é descobrir
        o endereço armazendo na variável `global_str`:
        
        ```
        (gdb) x/a 0x0000000000004028
        0x4028 <global_str>:    0x2004
        ```

        Agora basta usar o endereço para acessar a string armazenada na memória

        ```
        (gdb) x/s 0x2004
        0x2004: "Schiaparelli crater!"
        ```

