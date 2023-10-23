# 15 - Entrada/Saída

## Trabalhando com arquivos

Nesta seção trabalharemos com as chamadas `open`, `close`, `read` e `write`.

!!! exercise text short
    Leia o código do arquivo `exemplo_io1.c`. O quê ele faz?

    !!! answer "Resposta"
        Lê os 5 primeiros caracteres de um arquivo. O arquivo lido é passado via terminal.


Vamos agora usar o comando `man` para ver a documentação das chamadas de sistema do Linux. Digite no terminal `man read`. A tela mostrada contém a documentação da função `read`, incluindo sua assinatura e quais cabeçalhos devem ser incluídos para que ela possa ser usada.

<div class="termy">

    ```console
    $ man read
    ```

</div>

!!! exercise text short
    Usando como apoio a documentação aberta pelo comando `man`, como saber que um arquivo foi lido até o fim?

    **Dica**: a seção `RETURN VALUE` pode te ajudar.

    !!! answer "Resposta"
        A função `read` retorna o número de caracteres efetivamente lidos. Ela retorna 0 quando o arquivo acabou. A função só retorna quando os caracteres forem lidos, então ela pode bloquear o programa.

!!! tip
    Para acelerar suas buscas no `man` você pode ativar a busca pressionando `/`. Aí basta digitar o termo procurado. Para avançar para as próximas ocorrências de um termo basta apertar `/` + `Enter`.

!!! example
    Baseado em sua resposta acima, modifique `exemplo_io1.c` para que ele mostre o arquivo inteiro. Para ficar melhor de visualizar o resultado, faça o `printf` interno mostrar somente o caractere lido.

Vamos agora trabalhar com a chamada `write`. Um exemplo de seu uso está mostrado no arquivo `exemplo_io2.c`.

!!! exercise text short
    Abra o arquivo `exemplo_io2.c` e explique abaixo como usar `write`. Se ficar em dúvida use o manual (`man write`).

    !!! answer "Resposta"
        `write` recebe o identificador do arquivo, um endereço de memória e o número de bytes que devem ser copiados deste endereço para o arquivo.

<div class="termy">

    ```console
    $ man write
    ```

</div>

!!! example
    Em um novo arquivo `copy_file.c`, crie um programa `copy_file` que recebe dois nomes de arquivos como argumentos no terminal e copia o conteúdo do primeiro para o segundo. Ou seja, você deverá
    
    1. abrir ambos arquivos (cada um terá seu próprio *file descriptor*) 
    2. ler do primeiro para um buffer
    3. escrever este buffer no segundo

!!! tip "Validando"
    Após compilar, teste sua solução com um arquivo qualquer e utilize `diff` ou `cmp` para comparar os arquivos.

<div class="termy">

    ```console
    $ ./copy_file arquivo_origem.txt arquivo_destino.txt
    $ diff arquivo_origem.txt arquivo_destino.txt
    $ cmp arquivo_origem.txt arquivo_destino.txt
    ```

</div>


### Extra

Estes exercícios não terão correção durante a aula e devem ser checados no atendimento. Faça-os se você já acabou os anteriores e a correção/discussão ainda não começou.

Até agora trabalhamos com um buffer com somente um caractere. Isso facilita a programação, mas deixa nosso código muito lento.

!!! example
    Modifique o `copy_file` para usar um buffer de 100 caracteres. Meça o tempo de execução para a cópia de um arquivo grande (~100Mb) usando o comando `time`. Não se esqueça de verificar que os resultados ficaram iguais com o comando `diff`.

!!! tip
    Você pode utilizar o comando `dd` para gerar um arquivo aleatório de tamanho arbitrário. Por exemplo, para gerar um arquivo de 100MB, podemos fazer:


<div class="termy">

```console
$ dd if=/dev/urandom of=ex.bin bs=1M count=100 iflag=fullblock
```

</div>


!!! warning
    Não sabe como usar `time` ou `diff`? Use o comando `man` visto acima.

<div class="termy">

    ```console
    $ man time
    $ man diff
    ```

</div>

!!! exercise text short
    Você consegue explicar a diferença de desempenho entre as duas versões?

    !!! answer "Resposta"
        Ter disponível o buffer aumentado faz com que o programa tenha que acessar menos vezes a fila de IO, provendo ganho de performance.

## Permissões e posse de arquivos

No `exemplo_io2.c` passamos algumas opções extras para poder criar o arquivo:

~~~{.c}
int fd1 = open(arq1, O_WRONLY | O_CREAT, 0700);
~~~

A flag `O_CREAT` é usada para indicar que o arquivo deve ser criado caso ele não exista. O número `0700` representa os bits de acesso visto na expositiva. Cada dígito contém 3 dígitos que representam as seguintes permissões

* 4 - permissão de leitura
* 2 - permissão de escrita
* 1 - permissão de execução

O primeiro dígito contém as permissões do usuário dono do arquivo. O segundo dígito contém as permissões do grupo dono do arquivo. Usuários que pertencem a este grupo possuem estas permissões. O terceiro dígito lista as permissões para todos os outros usuários.

!!! exercise text short
    Use `ls -l` na pasta do arquivo criado por `copy_file` (ou por `exemplo_io2`). Onde é possível obter as informações de permissões do arquivo? Qual o usuário e grupo donos do arquivo? As permissões passadas para o `open` foram corretamente colocadas no arquivo?

    !!! answer "Resposta"
        A primeira coluna contém as permissões na ordem leitura (`r`), escrita (`w`) e execução (`x`) para o dono do arquivo, o grupo principal do arquivo e todos os usuários. É usado o caractere `-` para as permissões não concedidas. A segunda coluna mostra o usuário dono do arquivo. A terceira mostra o grupo dono do arquivo.

!!! exercise text short
    Quais permissões são garantidas pela máscara `640`? É uma boa ideia usá-la?

    !!! answer "Resposta"
        Leitura e escrita para o dono, leitura para o grupo e nenhuma permissão para outros usuários. Ela é interessante pois permite edição somente pelo dono, mas permite leitura para alguns usuários que o dono confia. Porém, não permite que qualquer usuário leia nem escreva no arquivo. 

!!! exercise text short
    Qual máscara usaria se quisesse que um arquivo possa ser modificado somente por seu dono, mas possa ser executado por qualquer usuário do sistema (incluindo o dono do arquivo)? Justifique.

    !!! answer "Resposta"
        755

!!! exercise text short
    Rode o comando `copy_file` usando `sudo`. Use `ls -l` para listar as informações do arquivo. Escreva abaixo quem é seu dono e suas permissões de acesso.

    !!! answer "Resposta"
        Confira no output do `ls -l`. Se ainda restar dúvida, confira com o professor

!!! example
    Use os comandos `chown` para mudar o dono do arquivo para seu usuário e `chmod` para deixar suas permissões como leitura e escrita para você e somente leitura para o restante.

    **Dica**: não sabe como usar os comandos acima? Use `man`.

<div class="termy">

    ```console
    $ man chown
    ```

</div>

### Extra

Estes exercícios trabalham com o conceito de posse de arquivos e de sobrescrita de arquivos já existentes.

!!! exercise text short
    Tente usar `copy_file` usando como fonte algum arquivo que você não possui acesso de leitura (você pode criá-lo e depois usar `chmod` para editar os acessos). O quê ocorre? Você consegue explicar este comportamento?

    !!! answer "Resposta"
        Confira com o professor

!!! example
    Conserte o erro ocorrido acima checando a saída de `open`. Consulte o manual caso necessário. Não se esqueça de fazê-lo para o arquivo fonte e destino.

!!! exercise text medium
    Vamos realizar um experimento neste exercício:

    1. Crie um arquivo com 100 caracteres *a* e chame-o de `100a`;
    1. Crie um arquivo com 3 caracteres *b* e chame-o de `3b`;
    1. Use `copy_file` para copiar `3b` em cima de `100a`;
    1. Mostre o conteúdo do arquivo sobrescrito `100a`.

    Você consegue explicar o que ocorreu? Se sim, busque no manual uma flag que, ao ser passada para o `open`, evita que isto ocorra.

    !!! answer "Resposta"
        Confira com o professor

!!! example
    O `copy_file` sobrescreve arquivos sem dó. Use o manual para encontrar a flag que faz `open` falhar caso o arquivo de destino já exista e conserte seu programa para perguntar se o usuário deseja sobrescrever o arquivo. Note que isto conflita com seu exercício 6. Entenda como usar `errno` para que você consiga diferenciar os dois tipos de erros.

