# Lab de Processos

Nesse lab iremos trabalhar com bibliotecas, integração entre processos e multiprocessamento para a criação de um programa similar ao [`wget`](https://www.gnu.org/software/wget/). Nosso programa, chamado de `web_downloader`, fará o download de arquivos referênciados por uma URL, para tanto, utilizaremos a ferramenta `cURLInsper`.

A ferramenta `cURLInsper` é um executável de linha de comando que transfere dados de um servidor usando o protocolo HTTP. Para fazermos o download de uma URL podemos executar o `cURLInsper` no terminal, por exemplo:

`./cURLInsper https://insper.github.io/SistemasHardwareSoftware/index.html index.txt`

No exemplo, estamos tentando fazer o download da página `https://insper.github.io/SistemasHardwareSoftware/index.html/` e armazenando o arquivo `index.html` no arquivo `index.txt`.

O executável `cURLInsper` pode ter os seguintes retornos (return) em sua execução:

* Quando a **quantidade de parâmetros está incorreta**, o programa **retorna -1**;

* Quando um **download** é bem sucedido, o programa **retorna 0**; e

* Quando a URL não existe ou ocorre uma **falha no download**, o programa **retorna 1**.

Ultimament o executável `cURLInsper` está um pouco instável com um comportamento estranho (culpa talvez do último programador que deu manutenção no código), essa manutenção fez com que, as vezes, a ferramenta demore um tempo excessivo para realizar o download ou até mesmo falhe durante ele de forma inexplicável.

O programador que fez o última manutenção disse que quando o download falhar, o usuário pode executar novamente a ferramenta informando o número da tentiva, incrementando esse número a cada nova tentativa, até que o download seja bem sucedido, e acreditem, essa gambiarra funciona. Para o exemplo abaixo temos um erro de download.

`./cURLInsper https://insper.github.io/SistemasHardwareSoftware/index.html index.html`

Mas se passar o número da tentativa igual a `1` no último parâmetro da chamada do `cURLInsper`, o download funciona:

`./cURLInsper https://insper.github.io/SistemasHardwareSoftware/index.html index.html 1`

## Restrições

Este exercício serve como avaliação dos conceitos vistos na disciplina. Portanto, algumas restrições serão aplicadas ao código de vocês:

- todo trabalho com arquivos deverá ser feito usando as APIs POSIX vistas em aula. **Não é permitido o uso de funções da** `Standard I/O` para manipulação de arquivos, como por exemplo `fopen()`, `fread()` e `fclose()`. 
- se você usar algum trecho de código da documentação (ou de outra fonte), coloque uma atribuição em um comentário no código.
- Fica proibido o uso de ferramentas de geração de código automático por IA, como por exemplo o ChatGPT.

## Entrega

Você deverá colocar sua entrega na pasta `lab/02-lab-processos` em seu repositório de atividades, na branch principal. Não precisa soltar release/tag. Além disso, grave um vídeo mostrando a tela do funcionamento do seu programa apresentando cada uma das fases desenvolvidas, e por fim, **preencha o arquivo `README.md` informando até qual fase você conseguiu chegar e o link do vídeo do funcionamento da sua entrega**. Lembre-se de se atentar ao prazo de entrega definido [aqui!](../../sobre.md).

## Avaliação

O programa será avaliado de forma manual usando uma rubrica que descreve as funcionalidades implementadas. Quanto maior o número de funcionalidades maior será a nota. 

### **Fase 0**

- O programa não compila
- Não preencheu o arquivo `README.md`
- O programa não implementa algum dos requisitos da rubrica da fase  **1**.

**NOTA desta fase**: 0.0

### **Fase 1**

- O programa compila com warnings.
- O programa roda na linha de comando como abaixo:

`./web_downloader http://exemplo.com/pagina.html`

- A página acima deve ser salva em um arquivo com o seguinte formato:  `exemplo_com_pagina.html`, ou seja, ignorando `http://` e `https://`, substituindo todas barras e pontos (exceto o último) por `_`.

- Para fazer o download da URL informada o seu programa `web_downloader` deve fazer uma chamada do excutável `cURLInsper` utilizando a função `exec` conforme visto em aula, você não pode, por exemplo, usar a chamada da função **system**.
- Ao terminar de baixar uma página, caso tenha sucesso, você deverá mostrar a mensagem `{url} baixada com sucesso!`. Exemplo: `{https://insper.github.io/SistemasHardwareSoftware/index.html} baixada com sucesso!`
- Se o download falhar o seu programa deverá mostrar a mensagem `{url} não pode ser baixada.`. Exemplo: `{https://insper.github.io/SistemasHardwareSoftware/index.html} não pode ser baixada.`

**NOTA desta fase**: 2.0

### **Fase 2**

- O programa compila sem warnings.
- Não entregou o video explicando o funcionamento do programa.
- O programa recebe uma flag `-f` seguida pelo nome de um arquivo. Seu programa deverá ler o arquivo e fazer o download de cada url dentro do arquivo. Você pode supor que cada linha do arquivo contém exatamente uma URL. As regras para o nome do arquivo correspondente são as mesmas do item anterior.
- Nessa fase cada download das URLs do arquivo informado por linha de comando pode ser realizada de forma sequencial, abaixo um exemplo da chamada do seu programa `web_downloader` com o flat `-f`.  

`./web_downloader -f lista_download.txt`

**NOTA desta fase**: 4.0

### **Fase 3**
- Video explicando e mostrando a execução do programa em paralelo.
- O download de cada URL é feito em um processo separado e em paralelo. 
- Se o download falhar, por alguma razão, o seu programa deve realizar pelo menos mais duas tentativas de chamadas do executável `cURLInsper`, informando o número da tentativa na chamada do `cURLInsper`. A cada tentativa deve ser informado se conseguiu ou não baixar a URL.

**NOTA desta fase**: 6.0

### **Fase 4**

- O processo principal só termina depois que todos os arquivos foram baixados.
- Programa roda **sem erros no valgrind**.
- O programa abre até `N` processos em paralelo. Se houver mais que `N` urls então os processos deverão sempre existir no máximo `N+1` processos (`N` para fazer download mais o original). Esse valor é passado pela linha de comando via flag `-N`, conforme abaixo: 

`./web_downloader -f lista_download.txt -N 2`

Se nada for passado assuma `N=4`, por exemplo:

`./web_downloader -f lista_download.txt -N`


**NOTA desta fase**: 8.0

### **Fase 5**

- As mensagens de finalização de baixar uma página são mostradas sem estarem embaralhadas, mesmo caso vários processos terminarem ao mesmo tempo.
- Ao apertar Ctrl+C todas as transferências são paradas e os arquivos que não foram baixados até o fim são deletados e os processos filhos são encerrados.


**NOTA desta fase**: 10.0

**IMPORTANTE:** Considere as **fases como cumulativas**, ou seja, cada versão deve **manter as funcionalidades da fase anterior** e acrescentar novas. Por exemplo, a versão da **Fase  2**, além de ler o arquivo com várias URL, também deve funcionar com download direto passando apenas a URL (sem `-f arquivo`). 

Caso você não implemente alguma funcionalidade de uma determinada fase a nota atribuída será a da fase anterior.


### Prazo:

[Clique aqui!](../../sobre).
