# Lab de Processos

Nesse lab iremos trabalhar com bibliotecas e processos para a criação de um programa similar ao `wget`. Nosso programa, chamado de `web_downloader`, fará download de páginas web usando a biblioteca `libCurl`.

## Restrições

Este exercício serve como avaliação dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas aos código de vocês:

- todo trabalho com arquivos deverá ser feito usando as APIs POSIX vistas em aula. **Não é permitido o uso de funções da** `Standard I/O` para manipulação de arquivos, como por exemplo `fopen()`, `fread()` e `fclose()`. 
- seu programa deverá compilar sem warnings usando as opções `-Wall -Wno-unused-result -Og -g -lcurl`
- você deverá usar a biblioteca `libCurl` para realizar o download das páginas. Veja sua [documentação](https://curl.se/libcurl/c/libcurl-easy.html) para aprender a usá-la
- se você usar algum trecho de código da documentação (ou de outra fonte), coloque uma atribuição em um comentário no código.

## Entrega

Você deverá colocar sua entrega na pasta `lab/02-lab-processos` em seu repositório de atividades, na branch principal. Não precisa soltar release/tag.

## Avaliação

O programa será avaliado de forma manual usando uma rubrica que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades maior será a nota.

### **Fase 0**

- O programa não compila
- O programa não implementa algum dos requisitos da rubrica da fase  **1**.

**NOTA desta fase**: 0.0

### **Fase 1**

- O programa compila com warnings.
- O programa roda na linha de comando como abaixo, salvando o resultado como `exemplo_com_pagina.html`, ou seja, ignorando `http://` e `https://`, substituindo todas barras e pontos (exceto o último) por `_`.

`$> web_downloader https://pt.wikipedia.org/wiki/index.html`

**NOTA desta fase**: 2.0

### **Fase 2**

- O programa compila sem warnings.
- O programa recebe uma flag `-f` seguida pelo nome de um arquivo. Seu programa deverá ler o arquivo e fazer o download de cada url dentro do arquivo. Você pode supor que cada linha do arquivo contém exatamente uma URL. As regras para o nome do arquivo correspondente são as mesmas do item anterior.

`$> web_downloader -f lista_download.txt`

**NOTA desta fase**: 4.0

### **Fase 3**

- O download de cada página é feito em um processo separado e em paralelo. Você deve observar uma diminuição grande no tempo de download de páginas pequenas.
- Ao terminar de baixar uma página, você deverá mostrar a mensagem "{url} baixada com sucesso!"


**NOTA desta fase**: 6.0

### **Fase 4**

- O processo principal só termina depois que todos os arquivos foram baixados.
- O programa abre até `N` processos em paralelo. Se houver mais que `N` urls então os processos deverão sempre existir no máximo `N+1` processos (`N` para fazer download mais o original). Esse valor é passado pela linha de comando via flag `-N`, conforme abaixo: 

`$> web_downloader -f lista_download.txt -N 2`

Se nada for passado assuma `N=4`, por exemplo:

`$> web_downloader -f lista_download.txt -N`


**NOTA desta fase**: 8.0

### **Fase 5**

- Se o download falhar por alguma razão seu programa deverá mostrar a mensagem "{url} não pode ser baixada.". Nenhum arquivo deverá ser produzido neste caso.
- As mensagens de finalização de baixar uma página são mostradas sem estar embaralhadas mesmo se vários processos terminarem ao mesmo tempo.
- Ao apertar Ctrl+C todas as transferências são paradas e os arquivos que não foram baixados até o fim são deletados e os filhos são encerrados.

**NOTA desta fase**: 10.0

**Obs:** Considere as **fases como cumulativas**, ou seja, cada versão deve **manter as funcionalidades da fase anterior** e acrescentar novas. Ex: a versão da **Fase  2**, além de ler o arquivo com várias URL, também deve funcionar com download direto passando apenas a URL (sem `-f arquivo`).


### Prazo:

[Clique aqui!](../../sobre).