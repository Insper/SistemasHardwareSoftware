# Lab de Processos

Em um Sistema Operacional, por razões de segurança, as senhas dos usuários não são armazenadas em texto simples, mas sim como um *hash*. Quando um usuário tenta fazer login a senha digitada é criptografada (gerado um *hash*) para ser comparado com o *hash* armazenado. Dessa forma, não há necessidade de armazenar sua senha real.

Caso o usuário tenha utilizado letras maiúsculas e minúsculas, caracteres especiais e numeros é praticamente impossível restaurar a senha a partir do *hash*. No entanto, se a senha for simples, e estivermos dispostos a gastar algum tempo de CPU, é possível tentar todas as combinações de caracteres possíveis em uma senha (ataque de força bruta) até gerar um *hash* igual ao *hash* armazenado.

Neste lab você deve implementar o programa `cracker_insper.c` que recupera as senhas perdidas de usuários, a partir de uma parte conhecida da senha. Para tanto, utilizaremos a ferramenta `hashcat` que gera o *hash* de uma senha (o nome da ferramenta é uma brincadeira com o comando `cat` do *Linux* com préfixo *hash*). A ferramenta tem como entrada um *hash* da senha original, a parte conhecida da senha e uma *string* (**semente**), com pelo menos dois caracteres, usada no algoritmo de criptografia para iniciar o gerador de *hash*.

 O programa `hashcat` quebra o *hash* utilizando um algoritmo de criptografia, que gera  várias combinações de caracteres, começando com a parte conhecida da  senha. Caso a ferramenta tenha sucesso, a senha é impressa no terminal. Abaixo um exemplo de chamada e saída do executável `hashcat`:


```
$ ./hashcat xxhx0AsVpMTMU sysx???? aa
./hashcat: recuperando a senha para o hash [xxhx0AsVpMTMU].
./hashcat: senha [sysxpert] recuperada.
```

No exemplo acima é informado o *hash* `"xxhx0AsVpMTMU"`, associado a uma senha, e a parte conhecida da senha `"sysx"`, seguida de caracteres de interrogação (`?`), representando os caracteres desconhecidos, e por fim a *string* `"aa"` que representa a semente para o inicializar algoritmo de criptografia. Para entrada do exemplo acima o executável `hashcat` consegue recuperar a senha a partir da parte conhecida da senha.

Ao finalizar o executável `hashcat` pode retornar os seguintes valores:

* -1: quando a **quantidade ou tamanho dos argumentos está incorreta ou errada**

* 0: quando consegue finalizar normalmente e quebrar a senha

* 1: quando não consegue quebrar a senha


Ultimamente o executável `hashcat` está um pouco instável, com falhas e travamentos inesperados, culpa talvez do último estagiário que deu manutenção no código. Essa manutenção fez com que, as vezes, a ferramenta trave indefinidamente, nem `Ctrl+C` o finaliza. O executável também tem um erro inexplicável de acesso à memória, finalizado pelo SO com um sinal de *segmentation fault* (Falha de segmentação).

O estagiário que fez a manutenção informou que quando o `hashcat` falhar por acesso à memória ou ficar travado indefinidamente, o usuário pode executar novamente a programa alterando a semente usada para o inicializar algoritmo de criptografia. Acreditem, essa gambiarra funciona. Veja uma sequencia desses erros:

```
$ ./hashcat xxqJ7cKzV3v4E zip????? aa 
./hashcat: recuperando a senha para o hash [xxqJ7cKzV3v4E].
Falha de segmentação (imagem do núcleo gravada)
```

Para semente `"ab"` o programa trava indefinidamente, sendo necessário  enviar um sinal de `kill` a partir do *Shell* para finalizá-lo. Para descobrir o número do processo execute `ps -C hashcat` e depois `kill -9 <pid>`.

```
$ ./hashcat xxqJ7cKzV3v4E zip????? ab
```

Mas se passar a semente para `"ac"`, o executável consegue recuperar a senha:

```
$./hashcat xxq5aBqiB66j2 xz???? ac
./hashcat: recuperando a senha para o hash [xxqJ7cKzV3v4E].
./hashcat: senha [xzzzzy] recuperada.
```

## Entrega

O programa fonte `cracker_insper.c` já está na pasta `lab/02-lab-processos` em seu repositório de atividades (*github*), na *branch* principal, para entregar você só precisa fazer **upload**  (`git add . & git commit -m "fase#" & git push`) do arquivo fonte no seu repositório a **cada fase finalizada**. Não precisa criar *tag*. 

Lembre-se de se atentar ao prazo de entrega definido [aqui!](../entregas.md).


## Avaliação

O programa será avaliado de forma manual pelo professor da disciplina, utilizando rubricas que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades implementadas, maior será a nota.

Caso necessário, para validação das fases, poderá ser realizada uma **entrevista sobre a implementação desse laboratório**.


## Restrições

Esta atividade tem com objetivo avaliar dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas ao código:

- Todo o trabalho com arquivos deverá ser realizado utilizando as APIs POSIX vistas em aula. **Não é permitido o uso de funções da** `Standard I/O` para manipulação de arquivos, como, por exemplo, `fopen()`, `fdopen()`, `fread()` e `fclose()`.

- **As impressões no terminal da sua implementação devem seguir rigorosamente os exemplos apresentados nas fases**.

- Caso você utilize algum trecho de código da documentação (ou de outra fonte), inclua a devida atribuição em um comentário no código.

- **É proibido** o uso de ferramentas de **geração automática de código por IA**, como, por exemplo, o **ChatGPT**.

**O não cumprimento dessas restrições resultará na atribuição de nota zero para este laboratório.**


### **Fase 0**

- O programa `cracker_insper.c` não compila ou compila com *warnings*. Para compilar use: 

    ```
    gcc cracker_insper.c -Wall -Wno-unused-result -g -Og -o cracker_insper
    ```
- O programa não implementa algum dos requisitos da rubrica da **Fase 1**.

**NOTA desta fase**: 0.0

### **Fase 1**

- O programa `cracker_insper.c` compila **SEM** *warnings*.

- **Não preencheu** o arquivo `README.md`

- O programa roda na linha de comando como abaixo, recebendo os argumentos para o executável conforme abaixo, informando o nome do usuário, o *hash* da senha e parte da senha conhecida.

    ```
    $./cracker_insper fabio xxhx0AsVpMTMU sysx????
    ```

- Para recuperar a senha do usuário `fabio` o seu programa `cracker_insper.c` deve realizar uma chamada ao executável `hashcat` utilizando a função `execvp` conforme visto em aula. Você não pode, por exemplo, usar a chamada da função **system**.

- Caso seja informado o número de parâmetros incorreto no seu programa, este deve finalizar com uma mensagem de orientação.

    ```
    $ ./cracker_insper fabio
    ./cracker_insper: quantidade de argumentos informados errados.
    USE:
    ./cracker_insper <usuario> <hash> <prefixo_da_senha>
    ```

- As chamadas do executável `hashcat` você deve começar a string **`aa`** como a primeira semente para o algoritmo de criptografia. 

- Caso o `hashcat` tenha sucesso, ou seja, o `hashcat` **retornou 0**, o  seu programa, você deverá mostrar, após a mensagem do executável `hashcat` a mensagem abaixo:

    ```
    $ ./cracker_insper fabio xxhx0AsVpMTMU sysx????
    ./hashcat: recuperando a senha para o hash [xxhx0AsVpMTMU].
    ./hashcat: senha [sysxpert] recuperada.
    ./cracker_insper: senha do usuario {fabio} recuperada. 
    ```
    
    Se a recuperação falhar por acesso à memória ou não for possível recuperar a senha o seu programa deverá mostrar uma mensagem informando o usuário e qual foi a falha ocorrida, por exemplo:

    ```
    $ ./cracker_insper paulo xxHUf9zUctXNA miss???? 
    ./hashcat: recuperando a senha para o hash [xxHUf9zUctXNA].
    ./cracker_insper: falha de memoria na recuperacao da senha do usuario {paulo}.
    ```
    
    Ou quando não é possível recuperar a senha, como o **retornou igual 1** do executário `hashcat`.

    ```
    $ ./cracker_insper andre xxGGPN89YLcGY cse????
    ./hashcat: recuperando a senha para o hash [xxGGPN89YLcGY].
    ./hashcat: nao eh possivel recuperar a senha.
    ```

- Caso o seu programa `cracker_insper` fique travado devido à execução do `hashcat`, finalize-o com `Ctrl+C` e encerre o processo `hashcat` com o comando `kill` no *Shell*, a fim de evitar sobrecarga no sistema operacional.

    ```
    $ ./cracker_insper fabio xxC4UjY9eNri6 hello??? 
    ^C
    $
    ```

- Para essa e as outras fases, o programa `cracker_insper.c` deve imprimir exclusivamente as mensagens especificadas nos exemplos. Mensagens de depuração ou quaisquer saídas adicionais devem ser removidas antes da entrega.

**NOTA desta fase**: 2.0

### **Fase 2**

- A partir desta fase, **e para todas as fases seguintes**, você deverá entregar o arquivo `README.md` contendo as seguintes informações:
    - Seu nome e uma descrição das fases do laboratório que conseguiu completar;
    - Relato de quaisquer *bugs* ou erros identificados no seu programa;
    - Alguma decisão de *design* relevante que você gostaria de compartilhar.
    - Inclua também o link de um **vídeo explicativo**, com áudio e captura de tela visível, apresentando a execução da sua implementação.

- Nesta fase, você deve melhorar a versão implementada na fase anterior. Agora caso a ferramenta `hashcat` falhe por acesso à memória (*segmentation fault*), o seu programa deverá realizar uma nova tentativa, modificando a semente do algoritmo de criptografia. Por exemplo: se a execução inicial utilizar a string `aa`, na próxima tentativa você pode utilizar `ab`. Em geral, a senha já é recuperada na segunda tentativa. Ao conseguir recuperar a senha, informe a semente utilizada. Veja o exemplo de execução a seguir:

    ```
    $ ./cracker_insper paulo xxHUf9zUctXNA miss????
    ./hashcat: recuperando a senha para o hash [xxHUf9zUctXNA].
    ./cracker_insper: falha de memoria na recuperacao da senha do usuario {paulo}.
    ./hashcat: recuperando a senha para o hash [xxHUf9zUctXNA].
    ./hashcat: senha [missudad] recuperada.
    ./cracker_insper: senha do usuario {paulo} recuperada com a semente {ab}.
    ```

- Nesta fase você também deverá tratar o travamento indefinido da ferramenta `hashcat`. O seu programa  `cracker_insper.c` deve aguardar alguns segundos (por exemplo, 5 segundos) pela finalização do processo filho (`hashcat`).  Caso esse tempo seja excedido (*timeout*), o programa deve encerrá-lo utilizando o sinal `SIGKILL`, por meio da função `kill()` da biblioteca `signal.h`, em seguida, realizar uma nova tentativa com uma semente diferente. **Dica de implementação**: para que o seu programa aguarde a finalização do processo filho de forma não bloqueante, pesquise a utilização da função `waitpid(-1,...)` e leia atentamente o manual dessa função (`man waitpid`).

    ```
    $ ./cracker_insper fabio xxC4UjY9eNri6 hello??? 
    ./hashcat: recuperando a senha para o hash [xxC4UjY9eNri6].
    ./hashcat: senha [helloaac] recuperada.
    ./cracker_insper: senha do usuario {fabio} recuperada com a semente {ab}.
    ```

- Programa `cracker_insper.c` roda **sem erros no valgrind**. Para testar use:

    ```
    $ valgrind --leak-check=yes ./cracker_insper fabio xxhx0AsVpMTMU sysx????
    ```

**NOTA desta fase**: 5.0

### **Fase 3**

- Nesta fase, além das funcionalidades da **Fase 2**, que devem ser mantidas na **Fase 3**, o programa `cracker_insper.c` tem a opção de receber uma flag `-f` seguida pelo nome de um arquivo de senhas, informado por linha de comando. Seu programa deverá ler o arquivo e recuperar as senhas dos usuários armazenados dentro do arquivo, exemplo:
    
    ```
    $ ./cracker_insper -f senhas1.in
    ```

- Cada linha do arquivo deve ser tratado como um processo independente, e a recuperação das senhas pode ser realizada de forma sequencial, assim seu programa pode ler uma linha do arquivo de entrada, chamar o executável `hashcat`, receber a resposta e imprimir no terminal. Cada linha do arquivo conterá:
    - Nome de usuário (de 1 a 8 caracteres)
    - Hash de senha (13 caracteres)
    - Parte conhecida da senha (mais interrogações que representam caracteres desconhecidos), contém de 0 a 8 letras minúsculas seguidas de 0 a 8 pontos de interrogação. **Importante**: a soma da parte conhecida + os pontos de interrogação terão no máximo 8 caracteres.

- Esses três campos são separados por um único espaço. Todas as informações que fornecemos estão garantidas neste formato. Não se preocupe com nomes de usuário duplicados ou prefixos duplicados. Exemplo de arquivo de entrada (`senhas1.in`):

    ```
    fabio xxhx0AsVpMTMU sysx????
    paulo xxHUf9zUctXNA miss????
    andre xxGGPN89YLcGY cse????
    jose xxC4UjY9eNri6 hello??? 
    ```

- A partir desta fase você deverá utilizar o executável `hashcat` em modo silencioso, no qual não há saída no terminal. Para isso, basta colocar no final da chamada o argumento  `-f`, que fará com que o `hashcat` gere um arquivo com a senha encontrada. O nome do arquivo será o *hash* informado com extensão `.txt`, veja um exemplo de execução do `hashcat` com esse argumento. 

    ```
    $ ./hashcat xxhx0AsVpMTMU sysx???? aa -f
    $ ls xxhx0AsVpMTMU.txt 
    $ xxhx0AsVpMTMU.txt
    $ cat xxhx0AsVpMTMU.txt 
    sysxpert
    ```

- Abaixo há um exemplo da chamada do seu programa com o *flag* `-f` com o arquivo `senhas1.in`, juntamente com a respectiva saída no terminal. Observe que **cada linha do arquivo é processada sequencialmente**. Em cada tentativa de execução do `hashcat`, deve ser informado a linha do arquivo, o nome do **usuário** e **semente**. Caso a senha seja recuperada com sucesso, o programa deve informar o **usuário** e a **senha** correspondente. Os casos de falha do executável `hashcat` devem ser reportados conforme exemplo a seguir:

    ```
    $ ./cracker_insper -f senhas1.in
    linha 1: recuperando senha de {fabio} com semente {aa}.
    linha 1: senha do usuario {fabio} recuperada {sysxpert}.
    linha 2: recuperando senha de {paulo} com semente {aa}.
    linha 2: falha de memoria na recuperacao da senha do usuario {paulo}.
    linha 2: recuperando senha de {paulo} com semente {ab}.
    linha 2: senha do usuario {paulo} recuperada {missudad}.
    linha 3: recuperando senha de {andre} com semente {aa}.
    linha 3: nao eh possivel recuperar a senha do usuario {andre}.
    linha 4: recuperando senha de {jose} com semente {aa}.
    linha 4: timeout de espera para senha de {jose}.
    linha 4: recuperando senha de {jose} com semente {ab}.
    linha 4: senha do usuario {jose} recuperada {helloaac}.
    ```
- Importante: Como na **Fase 2** 


**NOTA desta fase**: 7.5

### **Fase 4**

- Nesta fase, você deve paralelizar a solução da **Fase 3**. O arquivo de senhas **deve ser processado em paralelo, e não mais sequencial**. No início da execução, o programa `cracker_insper.c` deverá carregar todas as linhas do arquivo de entrada e, para cada linha, disparar a execução do `hashcat`, e depois aguardar a finalização de todas as execuções e apresentar as saídas correspondentes.

- Abaixo um exemplo de execução do programa com o arquivo `senhas1.in`, juntamente com **uma possível saída**.  Note que deve ser informado a linha que foi processada, bem como os casos em que ocorreu falha na recuperação da senha.

    ```
    $ ./cracker_insper -f senhas1.in
    linha 1: recuperando senha de {fabio} com semente {aa}.
    linha 2: recuperando senha de {paulo} com semente {aa}.
    linha 3: recuperando senha de {andre} com semente {aa}.
    linha 4: recuperando senha de {jose} com semente {aa}.
    linha 1: senha do usuario {fabio} recuperada {sysxpert}.
    linha 2: falha de memoria na recuperacao da senha do usuario {paulo}.
    linha 2: recuperando senha de {paulo} com semente {ab}.
    linha 2: senha do usuario {paulo} recuperada {missudad}.
    linha 4: timeout de espera para senha de {jose}.
    linha 3: nao eh possivel recuperar a senha do usuario {andre}.
    linha 4: recuperando senha de {jose} com semente {ab}.
    linha 4: senha do usuario {jose} recuperada {helloaac}.
    ```

- Lembre-se que o programa `cracker_insper.c` deve imprimir exclusivamente as mensagens apresentadas nos exemplos. Mensagens de depuração ou quaisquer saídas adicionais devem ser removidas antes da entrega.

- Por fim, ao pressionar `Ctrl+C` no terminal, o programa `cracker_insper.c` deve encerrar todos os processos do `hashcat` que ainda estão executando ou travados, e remove todos os arquivos de senhas gerados.


**NOTA desta fase**: 10.0

**IMPORTANTE:** Considere as **fases como cumulativas**, ou seja, cada versão deve **manter as funcionalidades da fase anterior** e acrescentar novas. Por exemplo, a versão da **Fase  2**, você deveria passar nos testes do *valgrind*, isso passa valer para todas as seguintes da **Fase  2**. E em caso de dúvida consulte o professor. Caso você não implemente alguma funcionalidade de uma determinada fase a nota atribuída será a da fase anterior.


### Prazo:

[Clique aqui!](../entregas.md).
