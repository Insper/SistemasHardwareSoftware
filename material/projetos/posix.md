# Linux do Zero

Na aula [12 - Linux do zero](/aulas/12-linux-do-zero) compilamos um sistema Linux a partir do código fonte e montamos uma imagem bootavel manualmente. Vamos neste lab completar nosso sistema com alguns executáveis essenciais para o funcionamento básico do nosso sistema. 

* `echo`: mostra uma mensagem no terminal
* `cat`: mostra um arquivo 
* `head`: mostra as primeiras linhas de um arquivo
* `tail`: mostra as primeiras linhas de um arquivo
* `ls`: mostra os arquivos em uma pasta.
* `shell`: recebe comandos e executa programas. 
* `init`: primeiro processo rodado. Inicializa sistema e recolhe processos orfãos.

Seu trabalho será implementar estes comandos e incluí-los em seu sistema Linux criado na aula 12. Você irá substituir uma porção de executáveis do busybox por implementaçõs próprias. A avaliação será feita no sistema criado na aula 12.

O comportamento esperado dos programas deverá ser idêntico aos já presentes no Ubuntu. Vocês podem comparar a saída dos programas usando o comando `diff`. Quanto maior o número de opções implementadas maior será a nota do projeto. As seções abaixo definem quais opções são necessárias para obter cada conceito. 

O funcionamento de cada programa pode ser conferido usando o manual `man`.

## Conceito `D`

* Um script que compila os executáveis implementados é disponibilizado.
* `echo` foi implementado. Não é necessário implementar nenhuma flag da linha de comando.
* `cat` foi implementado. Não é necessário implementar nenhuma flag da linha de comando nem receber vários arquivos.

## Conceito `C`

* Um `shell` simples foi implementado. Ele permite
    - executar um programa e esperar por seu retorno. Repassa somente um argumento para os processos lançados
    - mudar de pasta atual
* `ls` foi implementado sem opções extras (somente para a pasta atual). Seu programa deverá produzir saída idêntica a `ls -1` no Ubuntu. 
* `head` foi implementado usando as opções padrão. Somente um arquivo é mostrado.
* `tail` foi implementado usando as opções padrão. Somente um arquivo é mostrado.

## Conceito `B+`

* `head` e `tail` foram implementados com a opção `-n`.
* `head`, `tail` e `cat` aceitam receber mais de um arquivo.
* `shell` suporta repassar um número arbitrário de argumentos para os processos lançados.
* `ls` aceita a opção `-l`.

## Conceito `A+`

* um programa `init` foi implementado. Ele executa os processos listados em `/etc/init.sh` em ordem e depois fica em loop infinito recolhendo processos orfãos. 