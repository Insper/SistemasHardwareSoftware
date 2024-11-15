# Lab de Processos

Em um Sistema Operacional, por razões de segurança, as senhas dos usuários não são armazenadas em texto simples e sim o seu hash. Quando um usuário tenta fazer login a senha digitada é criptografada (gerando um hash) para ser comparado com o hash armazenado. Dessa forma, não há necessidade de armazenar sua senha real.

Caso o usuário tenha utilizado letras maiúsculas e minúsculas, caracteres especiais e numeros é praticamente impossível reconstruir a senha a partir do hash.  No entanto, se a senha for simples, e estivermos dispostos a gastar algum tempo de CPU, é possível tentar todas as combinações de caracteres possíveis em uma senha (ataque de força bruta) até gerar um hash igual ao hash armazenado.

Nesse lab você deve implementar o programa **`recupera_senha.c`** que recupera a(s) senha(s) perdida(s) de usuário(s) a partir de uma parte conhecida da senha. Para tanto, utilizaremos a ferramenta `criptInsper` que é um executável de linha de comando, que tem como entrada um hash e a parte de uma senha, em seguida, a ferramenta tenta recuperar a senha original. Abaixo um exemplo de chamada do `criptInsper`:

```
$./criptInsper xxC4UjY9eNri6 hello...
```
No exemplo acima é informado o valor do hash `"xxsczBXm6z4zA"`, associado a uma senha, e a parte conhecida da senha `"hello"` seguida de pontos `.`, representando os caracteres desconhecidos. O programa `criptInsper` tentar gerar um hash igual ao informado, a partir de várias combinações de caracteres, começando com a parte conhecida. Para a entrada acima o `criptInsper` tem a seguinte saída no terminal.

```
./criptInsper: senha [helloaac] recuperada.
```
Além disso, o `criptInsper` salva a senha recuperada no arquivo com do hash informado `xxC4UjY9eNri6.txt` e retorna `0` para o terminal. O executável pode ter outros valores como retorno em sua execução:

* Quando a **quantidade de parâmetros está incorreta ou errada**, o executável **retorna -2**;

* Quando não é possível quebrar a senha a partir do hash informado, o executável **retorna -1**; e

* Quando consegue recuperar a senha, o executável **retorna 0**. 


Ultimamente o executável `criptInsper` está um pouco instável, com um comportamento estranho, culpa talvez do último programador que deu manutenção no código. Essa manutenção fez com que, as vezes, a ferramenta demore um tempo excessivo para recuperar a senha ou seja finalizado por conta de acesso indevido a memória (segmentation fault).

O programador que fez a manutenção disse que quando o `criptInsper` falhar por acesso à memória, o usuário pode executar novamente a ferramenta informando o número da tentiva, incrementando esse número a cada nova tentativa, até que a recuperação da senha seja bem sucedida, e acreditem, essa gambiarra funciona. Veja um exemplo desse tipo de erro:

```
$./criptInsper xxq5aBqiB66j2 xz....
Falha de segmentação (imagem do núcleo gravada)
```
Mas se passar o número da tentativa igual a `1` no último parâmetro da chamada do `criptInsper`, o executável consegue recurar a senha:

```
$./criptInsper xxq5aBqiB66j2 xz.... 1
./criptInsper: senha [xzzzzy] recuperada.
```

## Restrições

Esta atividade serve como avaliação dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas ao código de vocês:

- todo trabalho com arquivos deverá ser feito usando as APIs POSIX vistas em aula. **Não é permitido o uso de funções da** `Standard I/O` para manipulação de arquivos, como por exemplo `fopen()`, `fdopen()`, `fread()` e `fclose()`. 
- se você usar algum trecho de código da documentação (ou de outra fonte), coloque uma atribuição em um comentário no código.
- **Fica proibido** o uso de ferramentas de **geração de código automático por IA**, como por exemplo o **ChatGPT**.

**O não atendimento dessas restrições resultarão em atribuição da nota zero para esse lab.**

## Entrega

Você deverá colocar o programa fonte `recupera_senha.c` na pasta `lab/02-lab-processos` em seu repositório de atividades (github), na branch principal, e fazer **upload (push) do arquivo fonte no seu repositório**,  não precisa soltar tag. Além disso, grave um vídeo mostrando a tela do funcionamento do seu programa apresentando cada uma das fases desenvolvidas, e por fim, **preencha o arquivo `README.md` informando até qual fase você conseguiu chegar e o link do vídeo do funcionamento da sua entrega**. Lembre-se de se atentar ao prazo de entrega definido [aqui!](../sobre.md).

## Avaliação

O programa `recupera_senha.c` será avaliado de forma manual usando uma rubrica que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades maior será a nota. 

### **Fase 0**

- O programa `recupera_senha.c` não compila
- **Não preencheu** o arquivo `README.md`
- O programa não implementa algum dos requisitos da rubrica da **fase 1**.

**NOTA desta fase**: 0.0

### **Fase 1**

- **Preencheu** o arquivo `README.md`
- O programa `recupera_senha.c` compila com warnings.
- O programa roda na linha de comando como abaixo:

    ```
    $./recupera_senha fabio xxC4UjY9eNri6 hello...
    ```

- Para recuperar a senha do usuário `fabio` o seu programa `recupera_senha.c` deve fazer uma chamada do excutável `criptInsper` utilizando a função `exec` conforme visto em aula, você não pode, por exemplo, usar a chamada da função **system**.
- Caso o `criptInsper` tenha sucesso, ou seja, **retorne 0** ao seu programa, você deverá mostrar,  **obrigatoriamente**, a mensagem abaixo:

    ```
    senha do usuario {fabio} recuperada {helloaac}
    ```
    Se a recuperacao falhar o seu programa deverá mostrar a mensagem:

    ```
    falha na recuperacao da senha do usuario {fabio}
    ```
- Para inibir os prints gerados pelo executável `criptInsper`, você pode utilizar o trecho de código abaixo antes da chamada da função `exec`. 

    ```c
    //descarte padrão linux, dados enviados para o arquivo são completamente descartados
    int fd_null = open("/dev/null", O_WRONLY);
    //Redireciona a saida padrao (stdout) para /dev/null 
    dup2(fd_null, STDOUT_FILENO);
    close(fd_null);
    execvp(prog, args);
    ```

**NOTA desta fase**: 2.5

### **Fase 2**

- O programa  `recupera_senha.c` compila sem warnings.
- **Não entregou o video** explicando o funcionamento do programa.
- O programa `recupera_senha.c` recebe uma flag `-f` seguida pelo nome de um arquivo de senhas. Seu programa deverá ler o arquivo e recuperar as senhas dos usuários armazenados dentro do arquivo. 
- Nessa fase cada linha do arquivo deve ser tratado como um processo independente, e a recuperação das senhas pode ser realizada de forma sequencial, assim seu programa pode ler uma linha do arquivo de entrada, chamar o executável `criptInsper`, receber a resposta e imprimir no terminal. Cada linha do arquivo conterá:
    - Nome de usuário (1 a 8 caracteres)
    - Hash de senha (13 caracteres)
    - Parte conhecida da senha (mais pontos que representam caracteres desconhecidos) (1 a 8 caracteres, contém de 0 a 8 letras minúsculas seguidas de 0 a 8 pontos) 

- Esses três campos são separados por um único espaço. Não se preocupe com nomes de usuário duplicados ou prefixos duplicados. Todas as informações que fornecemos estão garantidas neste formato. Exemplo de arquivo de entrada (`senhas1.in`):
    ```
    fabio xxC4UjY9eNri6 hello...
    ana xxq5aBqiB66j2 xz....
    diego xxhx0AsVpMTMU sysx....
    jose xxGGPN89YLcGY cham....
    ```
  Abaixo um exemplo da chamada do seu programa com o flat `-f` para o arquivo `senhas1.in` com a respectiva saída.  
  ```
  $./recupera_senha -f senhas1.in
  Processo 1: recuperando senha de {fabio}
  Processo 1: senha do usuario {fabio} recuperada {helloaac}
  Processo 2: recuperando senha de {ana}
  Processo 2: falha na recuperacao da senha do usuario {ana}
  Processo 3: recuperando senha de {diego}
  Processo 3: senha do usuario {diego} recuperada {sysxpert}
  Processo 4: recuperando senha de {jose}
  Processo 4: falha na recuperacao da senha do usuario {jose} 
  2 senhas recuperadas, 2 falhas.
  ```

**NOTA desta fase**: 5.0

### **Fase 3**
- Entregou video explicando e mostrando a execução do programa.
- Programa `recupera_senha.c` roda **sem erros no valgrind**.
- Nessa fase cada linha do arquivo deve ser tratado como um processo independente, e a recuperação das senhas **deve** ser realizada em **paralelo**. Assim no início da execução o seu programa deverá carregar todos os processos do executável `criptInsper`, e somente depois aguardar a finalização dos processos criados.
- Se o executável `criptInsper` finalizar por segmentation fault, o seu programa deve realizar pelo menos mais duas tentativas de chamadas do executável `criptInper`, informando o número da tentativa na chamada do executável. A cada nova tentativa deve ser informado se conseguiu ou não recuperar a senha.
  
- Abaixo um exemplo da chamada do seu programa para o arquivo `senhas1.in` com **uma possível saída**.  
  ```
  $./recupera_senha -f senhas1.in
  Processo 1: recuperando senha de {fabio}
  Processo 2: recuperando senha de {ana}
  Processo 3: recuperando senha de {diego}
  Processo 4: recuperando senha de {jose}
  Processo 1: senha do usuario {fabio} recuperada {helloaac}
  Processo 2: falha na recuperacao da senha do usuario {ana}
  Processo 3: senha do usuario {diego} recuperada {sysxpert}
  Processo 4: falha na recuperacao da senha do usuario {jose}
  Processo 5: recuperando senha de {ana}
  Processo 5: senha do usuario {ana} recuperada {xzzzzy}
  3 senhas recuperadas, 1 falhas.
  ```

**NOTA desta fase**: 7.5

### **Fase 4**

- O programa `recupera_senha.c` abre até `N` processos do executável `criptInsper` **em paralelo** para recuperar as senhas no arquivo de entrada. Considere que nos testes sempre utilizaremos um arquivo com número de linhas maior que `N`. Esse valor é passado pela linha de comando via flag `-N`, conforme abaixo: 
    ```
    ./recurera_senha -f senhas1.in -N 2
    ```

    Se nada for passado assuma `N=4`, por exemplo:

    ```
    ./recurera_senha -f senhas1.in -N
    ```

- E por fim, ao apertar `Ctrl+C` no terminal, o programa `recupera_senha.c` finaliza os processos do `criptInsper` que ainda estão executando e apaga todos os arquivos de senhas que foram geradas.


**NOTA desta fase**: 10.0

**IMPORTANTE:** Considere as **fases como cumulativas**, ou seja, cada versão deve **manter as funcionalidades da fase anterior** e acrescentar novas. Por exemplo, a versão da **Fase  2**, além de ler o arquivo com várias senhas, também deve ser possível recuperar uma senha passada por linha de comando  (sem `-f arquivo`). 

Caso você não implemente alguma funcionalidade de uma determinada fase a nota atribuída será a da fase anterior.


### Prazo:

[Clique aqui!](../sobre.md).
