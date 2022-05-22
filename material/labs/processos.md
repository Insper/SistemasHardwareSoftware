# Immortal

No Lab de **Processos** iremos trabalhar com ferramentas e bibliotecas para criação de um **Monitor de Processos**. Nosso programa, chamado de  `immortal`, será responsável por subir programas e monitorar seus processos, garantindo que seja reiniciado sempre que finalizado.

## Onde desenvolver?
Foi criado uma pasta `lab/02-immortal` em seu repositório de entregas da disciplina. Edite o arquivo `immortal.c` para resolver seu lab!

Para compilar, utilize obrigatoriamente:
<div class="termy">

    ```console
    $ gcc -Wall -Wno-unused-result -Og -g immortal.c -o immortal
    ```

</div>

## Restrições

Este exercício serve como avaliação dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas aos código de vocês:

- todo trabalho com arquivos, processos e sinais deverá ser feito usando as APIs POSIX vistas em aula
- seu programa deverá compilar sem warnings usando as opções `-Wall -Wno-unused-result -Og -g`
- se você usar algum trecho de código da documentação (ou de outra fonte), coloque uma atribuição em um comentário no código.

## Avaliação

O programa será avaliado usando uma rubrica que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades maior será a nota. Apesar de cada conceito envolver a entrega de uma tab no servidor de testes, a nota final da atividade será o maior conceito implementado, considerando que passou em todos os anteriores. Ex:
- Se passar na D, não passar na C, passar na B, não passar na A a nota final será D.
- Se passar na D, C e B, mas não passar na A, a nota final será B.

**Atenção:** Os testes automáticos serão nossa forma principal de avaliação. Entretanto, o professor poderá utilizar processos extras de avaliação, como: entrevistas, revisão manual de código.

### Conceito **I**

- O programa não compila
- O programa não implementa algum dos requisitos da rubrica **D**.

### Conceito **D**

- O programa compila com warnings.
- O programa roda na linha de comando como abaixo, iniciando o `programa` apontado em um processo filho.
<div class="termy">

    ```console
    $ ./immortal -p programa
    ```

</div>

- Sempre que o processo do `programa` for finalizado (seja qual for o motivo), o `programa` deve ser iniciado novamente em um novo processo filho em no máximo 2 segundos.
- Nesta versão não será possível passar argumentos pelo terminal para o `programa` filho.
- Para entregar, lance uma tag `lab2.0.x`:
<div class="termy">

    ```console
    $ git tag -a lab2.0.0 -m "lab2.0.0"
    $ git push origin lab2.0.0
    ```

</div>

### Conceito **C**

- O programa compila sem warnings.
- O programa recebe uma flag `-f` seguida pelo nome de um arquivo de texto (Exemplo: `programs.imt`). Seu programa deverá ler o arquivo e subir todos os programas nele indicados.

<div class="termy">

    ```console
    $ ./immortal -f programs.imt
    ```

</div>

- Cada programa indicado no arquivo deve ser subido em um processo diferente.
- Cada linha do arquivo `programs.imt` conterá APENAS o path do programa a ser aberto (sem argumentos da linha de comando).
- A funcionalidade `-p programa` (Conceito D) deverá continuar funcionando.
- Considere que o usuário irá utilizar obrigatoriamente uma das flags `-p` ou `-f` (mas não ambas).
- Para entregar, lance uma tag `lab2.1.x`:
<div class="termy">

    ```console
    $ git tag -a lab2.1.0 -m "lab2.1.0"
    $ git push origin lab2.1.0
    ```

</div>

### **Conceito B**
<!-- - Você deve atualizar a versão C possibilitando indicar no arquivo passado para a flag `-f` (Exemplo: `programs.imt`) argumentos para cada programa a ser monitorado.
- Cada linha do arquivo `programs.imt` conterá o path do programa a ser aberto E seus argumentos da linha de comando. -->
- Ao apertar Ctrl+C o programa `immortal` pergunta se o usuário deseja realmente sair. Se `Y` ou `y`, todos os processos filhos são encerrados **antes** que o pai encerre (envie sinal). **OBS:** a entrada do usuário deve ser obrigatoriamente `Y` ou `y`. Caso contrário, ignore e continue.
- As funcionalidades das versões anteriores devem continuar disponíveis.
- Para entregar, lance uma tag `lab2.2.x`:
<div class="termy">

    ```console
    $ git tag -a lab2.2.0 -m "lab2.2.0"
    $ git push origin lab2.2.0
    ```

</div>

### Conceito **A**

- O programa recebe uma flag `-l` (*L minúsculo*) seguido do path de um arquivo. Você deve gerar um log neste arquivo.
- Caso o arquivo de log não exista, crie. Se já existir, adicione novos logs no final, sem sobrescrever.
- As mensagens do log devem seguir o padrão (uma linha por evento):

```
starting ./infinito (pid=184085)
starting ./timecrash (pid=184086)
starting ./timetogo (pid=184088)
program ./timecrash (pid=184086) finished (EXITED=0, EXITSTATUS=0, SIGNALED=1, SIGNAL=8, SIGNALSTR=Floating point exception)
restarting ./timecrash (oldpid=184086, newpid=184094)
program ./timetogo (pid=184088) finished (EXITED=1, EXITSTATUS=0, SIGNALED=0, SIGNAL=0, SIGNALSTR=Unknown signal 0)
restarting ./timetogo (oldpid=184088, newpid=184129)
program ./timecrash (pid=184094) finished (EXITED=0, EXITSTATUS=0, SIGNALED=1, SIGNAL=8, SIGNALSTR=Floating point exception)
restarting ./timecrash (oldpid=184094, newpid=184131)
```
- Obs: ao receber um CTRL+C (SIG_INT), ao sair do immortal não precisa incluir no log a finalização dos processos filhos.
- As funcionalidades das versões anteriores devem continuar disponíveis.
- Considere que o usuário irá utilizar obrigatoriamente uma das flags `-p` ou `-f` (mas não ambas). Já o uso da flag `-l` será opcional.
- As flags podem ser utilizadas em qualquer ordem: `./immortal -f programs.imt -l mylog.log` ou `./immortal -l mylog.log -f programs.imt`.
- Exemplo de uso:
<div class="termy">

    ```console
    $ ./immortal -f programs.imt -l mylog.log
    ```

</div>
- Para entregar, lance uma tag `lab2.3.x`:
<div class="termy">

    ```console
    $ git tag -a lab2.3.0 -m "lab2.3.0"
    $ git push origin lab2.3.0
    ```

</div>

### Prazo:

[Clique aqui!](../../sobre).
<!-- 
## Gabarito
Para facilitar o desenvolvimento do projeto, fornecemos executáveis que implementam cada versão solicitada nos labs. Eles estão disponíveis no seu repositório de atividades na pasta `lab\02-immortal\tests\util\gabarito\lab2.x.x`.

Confira nas próximas sub-seções exemplos de uso!

## Rubrica D: tag **lab2.0.x**

## Rubrica C: tag **lab2.1.x**

## Rubrica B: tag **lab2.2.x**

## Rubrica A: tag **lab2.3.x**
 -->
