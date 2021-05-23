# Lab de Threads

Agora que já temos uma versão de `web_downloader` usando processos iremos reimplementá-lo usando threads. Com isso, poderemos comparar o quão fácil (ou difícil) cada funcionalidade é de implementar com cada tecnologia e quais as vantagens e desvantagens de usar processos e threads para implementar programas concorrentes.

## Restrições

Este exercício serve como avaliação dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas aos código de vocês. Isso significa que algumas APIs de alto

- todo trabalho com arquivos deverá ser feito usando as APIs POSIX vistas em aula;
- seu programa deverá compilar sem warnings usando as opções `-Wall -Wno-unused-result -Og -g -lcurl -pthread`
- você deverá usar a biblioteca `libCurl` para realizar o download das páginas. Veja sua [documentação](https://curl.se/libcurl/c/libcurl-easy.html) para aprender a usá-la.
- se você usar algum trecho de código da documentação (ou de outra fonte), coloque uma atribuição em um comentário no código.

## Avaliação

O programa será avaliado usando uma rubrica que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades maior será a nota.

### Conceito **I**

- O programa não compila
- O programa não implementa algum dos requisitos da rubrica  **D**.

### Conceito **D**

- O programa compila com warnings
- O programa roda na linha de comando como abaixo, salvando o resultado como `exemplo_com_pagina.html` (ou seja, substituindo todas barras e pontos por `_`)

`$> web_downloader http://exemplo.com/pagina.html`

- O programa recebe uma flag `-f` seguida pelo nome de um arquivo. Seu programa deverá ler o arquivo e fazer o download de cada url dentro do arquivo. Você pode supor que cada linha do arquivo contém exatamente uma URL. As regras para o nome do arquivo correspondente são as mesmas do item anterior.

`$> web_downloader -f lista_download.txt`


### Conceito **C**

- O programa compila sem warnings.
- O download de cada página é feito em uma thread.
- Ao terminar de baixar uma página, você deverá mostrar a mensagem "{url} baixada com sucesso!"
- O programa principal só termina depois que todos os arquivos foram baixados.

### **Conceito C+**

- As mensagens de finalização de baixar uma página são mostradas sem estar embaralhadas mesmo se várias threads terminarem ao mesmo tempo. As mensagens deverão ser mostradas assim que o download for finalizado.
- Se o download falhar por alguma razão seu programa deverá mostrar a mensagem "{url} não pode ser baixada.". Nenhum arquivo deverá ser produzido neste caso. Essas mensagens também não podem estar embaralhadas. 

### Conceito **B+**

- O programa abre até `N` threads em paralelo. Esse valor é passado pela linha de comando via flag `-N`. Se nada for passado assuma `N=4`. Este item corresponde a implementar um produtor-consumidor básico usando threads. 
- Ao apertar Ctrl+C o programa pergunta se o usuário deseja realmente sair. Se sim, todas as transferências são paradas e os arquivos que não foram baixados até o fim são deletados.

### Conceito **A**

- Ao receber a flag `-r` o programa faz a análise de links (usando PCRE) nas páginas baixadas e coloca esses links na fila de páginas a baixar também. A análise de links só é feita nos links originais e não nos das páginas "filhas".
- Cada página deverá ser guardada em uma pasta `{url}_links`.
