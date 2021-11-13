# Lab de Processos e Bibliotecas

No lab de Sistemas Operacionais iremos trabalhar com bibliotecas e processos para a criação de um programa similar ao `wget`. Nosso programa, chamado de  `web_downloader`, fará download de páginas web usando a biblioteca `libCurl`.

## Restrições

Este exercício serve como avaliação dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas aos código de vocês:

- todo trabalho com arquivos deverá ser feito usando as APIs POSIX vistas em aula
- seu programa deverá compilar sem warnings usando as opções `-Wall -Wno-unused-result -Og -g -lcurl`
- você deverá usar a biblioteca `libCurl` para realizar o download das páginas. Veja sua [documentação](https://curl.se/libcurl/c/libcurl-easy.html) para aprender a usá-la
- se você usar algum trecho de código da documentação (ou de outra fonte), coloque uma atribuição em um comentário no código.

## Avaliação

O programa será avaliado usando uma rubrica que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades maior será a nota. Você deverá colocar sua entrega na pasta `lab-processos` na raiz do repositório de atividades.

### Conceito **I**

- O programa não compila
- O programa não implementa algum dos requisitos da rubrica  **D**.

### Conceito **D**

- O programa compila com warnings.
- O programa roda na linha de comando como abaixo, salvando o resultado como `exemplo_com_pagina.html`, ou seja, ignorando `http://` e `https://`, substituindo todas barras e pontos (exceto o último) por `_`.

`$> web_downloader http://exemplo.com/pagina.html`

### Conceito **C**

- O programa compila sem warnings.
- O programa recebe uma flag `-f` seguida pelo nome de um arquivo. Seu programa deverá ler o arquivo e fazer o download de cada url dentro do arquivo. Você pode supor que cada linha do arquivo contém exatamente uma URL. As regras para o nome do arquivo correspondente são as mesmas do item anterior.

`$> web_downloader -f lista_download.txt`

- O download de cada página é feito em um processo separado e em paralelo. Você deve observar uma diminuição grande no tempo de download de páginas pequenas.
- Ao terminar de baixar uma página, você deverá mostrar a mensagem "{url} baixada com sucesso!"

### **Conceito B**

- O processo principal só termina depois que todos os arquivos foram baixados.
- O programa abre até `N` processos em paralelo. Se houver mais que `N` urls então os processos deverão sempre existir no máximo `N+1` processos (`N` para fazer download mais o original). Esse valor é passado pela linha de comando via flag `-N`. Se nada for passado assuma `N=4`.

### Conceito **A**

- As mensagens de finalização de baixar uma página são mostradas sem estar embaralhadas mesmo se vários processos terminarem ao mesmo tempo.
- Ao apertar Ctrl+C o programa pergunta se o usuário deseja realmente sair. Se sim, todas as transferências são paradas e os arquivos que não foram baixados até o fim são deletados.
- Se o download falhar por alguma razão seu programa deverá mostrar a mensagem "{url} não pode ser baixada.". Nenhum arquivo deverá ser produzido neste caso.
