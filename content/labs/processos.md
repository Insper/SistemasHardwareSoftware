# Lab de Processos

Nesse laboratório iremos trabalhar com bibliotecas e processos para a criação de um programa similar ao [`wget`](https://www.gnu.org/software/wget/). Você implementará o programa, chamado de `./web_downloader`, que fará *download* de documentos da *Internet* (páginas, imagens, arquivos, etc) a usando a biblioteca [`libCur`](https://curl.se/libcurl/c/allfuncs.html). Nesse [link](https://curl.se/libcurl/c/example.html) você terá acesso a vários exemplos de códigos usando a biblioteca `libCur`. 

O código para seu programa deve ser escrito no arquivo `web_downloader.c`, que estará em branco sem nenhuma função, isto desafiará suas habilidades de desenvolvedor, pois terá que aprender a usar diversas funções das bibliotecas da linguagem `C`. 
Uma sugestão é que para cada função nova que for utilizar, teste o seu funcionamento (entrada e saída) em um programa separado para depois utilizar na implementação do `web_downloader.c`.
É **muito importante** que você leia com atenção as especificações das funções no manual da função (para isso você pode usar o comando `man` no terminal). A seguir seguem algumas boas boas práticas de programação que poderão lhe ajudar:

+ **Planeje a totalidade da sua tarefa**: Crie um esqueleto de como todo o seu código ficará. Isso evitará que você precise reestruturar todo o seu código para adicionar um único recurso novo;
+ **Estruture seu código em funções modulares**: Você não quer depurar um `while` de `1500` linhas dentro de `main`;
+ **Trabalhe incrementalmente**: Implemente um recurso, teste, depure, siga em frente; e
+ **Faça o código legível**: Uma boa nomenclatura e espaçamento tornarão seu código muito mais legível.

Para compilar o seu programa use:

```Shell
gcc -Wall -Wno-unused-result -Og -g web_downloader.c -lcurl -o web_downloader
```

Caso a compilação não encontre a biblioteca `libCurl` utlize o comando de instalação:
  
```sh
sudo apt update
sudo apt upgrade 
sudo apt-get install libcurl4-gnutls-dev
```

## Restrições

Este atividade serve como avaliação dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas ao desenvolvimento dessa atividade:

- todo trabalho com arquivos deverá ser feito usando as APIs POSIX vistas em aula. **Não é permitido o uso de funções da** `Standard I/O` para manipulação de arquivos, como por exemplo `fopen()`, `fdopen()`, `fread()` e `fclose()`. 

- você deverá usar a biblioteca `libCurl` para realizar o *download* dos documentos. Veja sua [documentação](https://curl.se/libcurl/c/libcurl-easy.html) para aprender a usá-la

- se você usar algum trecho de código da documentação (ou de outra fonte), coloque uma atribuição em um comentário no código.

- **Fica proibido** o uso de ferramentas de **geração de código automático por IA**, como por exemplo o **ChatGPT**.

**O não atendimento dessas restrições resultarão em atribuição da nota zero para esse lab.**

## Entrega

Você deverá colocar sua entrega na pasta `lab/02-lab-processos` em seu repositório de atividades (github), na *branch* principal, e e fazer **upload (push) do arquivo fonte no seu repositório**. 

Além disso, grave um vídeo mostrando a tela do funcionamento do seu programa **apresentando cada uma das fases desenvolvidas**, e por fim, preencha o arquivo `README.md` informando até qual fase você conseguiu chegar e o link do vídeo do funcionamento da sua entrega.

## Avaliação

O programa será avaliado de forma manual, pelo professor da disciplina, usando uma rubrica que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades maior será a nota. Caso o professor julgue necessário, para validar a nota das fases, poderá ser realizada uma **entrevista referente a implementação do laboratório**.


### **Fase 0**

- O programa não compila

- Não preencheu o arquivo `README.md`.

- O programa não implementa algum dos requisitos da rubrica da fase  **1**.

**NOTA desta fase: 0.0**

### **Fase 1**

- A partir dessa fase você deve entregar o arquivo `README.md` com as seguintes informações:
    - Seu nome e uma descrição de qual fase do lab você conseguiu completar;
    - Relate também quaisquer *bugs* ou erros identificados no seu programa;
    - Alguma decisão de *design* interessante que você gostaria de compartilhar.

- O programa compila **com** *warnings*.

- O programa roda na linha de comando como abaixo, salvando o resultado como `exemplo_com_pagina.html`, ou seja, ignorando `http://` e `https://`, substituindo todas barras e pontos (exceto o último) por `_`.

    ~~~sh
    ./web_downloader https://pt.wikipedia.org/wiki/index.html
    ~~~

    nesse caso, o arquivo seria salvo com o nome: `pt_wikipedia_org_wiki_index.html`. Caso a URL não tenha o nome do arquivo, como exemplo abaixo:

    ~~~sh
    ./web_downloader https://www.wikipedia.org/
    ~~~

    O arquivo terá o seguine nome `www_wikipedia.org`

- Programa `./web_downloader` roda **sem erros no valgrind**. Para testar o seu program use: 

    ```
    valgrind --leak-check=yes ./web_downloader https://pt.wikipedia.org/wiki/index.html
    ```

**NOTA desta fase: 2.0**

### **Fase 2**

- O programa compila **sem** *warnings* e (é claro) continua rodando **sem erros no valgrind**.

- O programa recebe uma flag `-f` seguida pelo nome de um arquivo. Seu programa deverá ler o arquivo e fazer o *download* de cada URL dentro do arquivo. Você pode supor que cada linha do arquivo contém exatamente uma URL. As regras para o nome do arquivo correspondente são as mesmas do item anterior. A chamada do programa pode ser feita conforme abaixo:

  ``` sh
  ./web_downloader -f lista_download.txt
  ```

- Não entregou **video explicativo**

**NOTA desta fase: 4.0**

### **Fase 3**

- **Atende todos os requisitos das fases anteriores** e a partir dessa fase você deve entregar o arquivo `README.md`, com as orientações informadas na **Fase 1** e **video explicativo** com áudio e a tela de visível com a execução da implamentação, não esqueça de colocar o link do vídeo no no arquivo `README.md`

- O *download* de cada documento é feito em um processo separado e **em paralelo**. Você deve observar uma diminuição grande no tempo de *download* de documentos.

- Ao terminar de baixar um documento, você deverá mostrar a mensagem "{url} baixada com sucesso pelo processo {pid}!"


**NOTA desta fase: 6.0**

### **Fase 4**

- **Atende todos os requisitos das fases anteriores** e o processo principal só termina depois que todos os arquivos foram baixados.

- O programa abre **até `N` processos em paralelo**. Se houver mais que `N` URLs, então cada processo deverá lidar com mais de uma URL mantendo a quantia de no máximo `N+1` processos (`N` para fazer *download* mais o original). Esse valor é passado pela linha de comando via flag `-N`, conforme abaixo: 

  ```sh
  ./web_downloader -f lista_download.txt -N 2
  ```

  Se nada for passado assuma `N=4`, por exemplo:

  ```sh
  ./web_downloader -f lista_download.txt -N
  ```
**NOTA desta fase: 8.0**

### **Fase 5**

- **Atende todos os requisitos das fases anteriores** e se o *download* falhar por alguma razão seu programa deverá mostrar a mensagem "{url} não pode ser baixada.". Nenhum arquivo deverá ser produzido neste caso.

- As mensagens de finalização de baixar um documento são mostradas sem estar embaralhadas mesmo se vários processos terminarem ao mesmo tempo.

- Ao apertar `Ctrl+C` todas as transferências são paradas e os arquivos que não foram baixados até o fim são deletados e os filhos são encerrados.

**NOTA desta fase: 10.0**

### Importante 

Considere as **fases como cumulativas**, ou seja, cada versão deve **manter as funcionalidades da fase anterior** e acrescentar novas. Ex: a versão da **Fase  2**, além de ler o arquivo com várias URL, também deve funcionar com *download* direto passando apenas a URL (sem `-f arquivo`).


### Prazo:

[Clique aqui!](../../entregas).