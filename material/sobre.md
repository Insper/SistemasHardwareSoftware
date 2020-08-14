

# Plano de aulas

* SEG 13:30 - 15:40
* QUI 15:45 - 17:45

* Atendimento: QUI 14:00 - 15:30

??? note "Plano de aulas"


    | Data   | Questão/Problema                                                        | Conteúdo/Atividade                                                                                                                    |
    |:-------|:------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------------|
    | 24/08  | Mutirão C                                                               | Exercícios práticos de revisão                                                                                                        |
    | 27/08  | Mutirão C                                                               | Exercícios práticos de revisão                                                                                                        |
    | 31/08  | Como a CPU representa dados em baixo nível?                             | Representação de inteiros na CPU: números binários e hexadecimais, complemento de dois, operações bit a bit.                          |
    |        |                                                                         | Leitura: Cap 2 CS:APP; Cap 9 Stallings                                                                                                |
    | 03/09  | Como a CPU representa dados em baixo nível?                             | Representação de ponteiros, arrays e estruturas em RAM.                                                                               |
    |        |                                                                         | Leitura: Cap 2 CS:APP; Cap 9 Stallings                                                                                                |
    | 07/09  | FERIADO                                                                 | FERIADO                                                                                                                               |
    | 10/09  | Como a CPU representa e executa um programa escrito em C?               | Arquitetura de computadores: registradores, memória e endereçamento                                                                   |
    |        |                                                                         | Assembly: Organização de um executável no disco e na memória                                                                          |
    |        |                                                                         | Leitura: Cap 3.1 – 3.4 CS:APP                                                                                                         |
    | 14/09  | Como a CPU representa e executa um programa escrito em C?               | Arquitetura de computadores: chamadas de função e pilha                                                                               |
    |        |                                                                         | Assembly: Exercícios com chamadas de função e operações com inteiros                                                                  |
    |        |                                                                         | Leitura: Cap 3.5 CS:APP                                                                                                               |
    | 17/09  | Como a CPU representa e executa um programa escrito em C?               | Assembly: expressões booleanas e estruturas de controle condicionais                                                                  |
    | 21/09  | Como a CPU representa e executa um programa escrito em C?               | Assembly: estruturas de controle de loop                                                                                              |
    |        |                                                                         | Leitura: Cap 3.6 CS:APP                                                                                                               |
    | 24/09  | Como a CPU representa e executa um programa escrito em C?               | Revisão; organização de executável no disco e na memória                                                                              |
    |        |                                                                         | Assembly: variáveis locais, strings e arrays                                                                                          |
    |        |                                                                         | Leitura: Cap 3.7 – 3.8 CS:APP                                                                                                         |
    | 28/09  | Como a CPU representa e executa um programa escrito em C?               | Exercícios práticos de revisão                                                                                                        |
    | 01/10  | E se meu programa precisar de mais memória?                             | A função malloc e a alocação dinâmica de estruturas, arrays e strings.                                                                |
    |        |                                                                         | Uso da ferramenta valgrind para checagem de memória                                                                                   |
    |        |                                                                         | Leituras: Cap 16 Kochan (Prog in C); Cap 9.9 CS:APP                                                                                   |
    | 05/10  | E se meu programa precisar de mais memória?                             | Tipos Abstratos de dados e alocação dinâmica de memória                                                                               |
    |        |                                                                         | Leituras: Cap 6 K&R                                                                                                                   |
    | 08/10  | PROVA INTERMEDIÁRIA                                                     | PROVA INTERMEDIÁRIA                                                                                                                   |
    | 12/10  | FERIADO                                                                 | FERIADO                                                                                                                               |
    | 15/10  | O que é um sistema operacional? Como os programas se comunicam com ele? | Visão global de um sistema: kernel, sistema de arquivos, biblioteca padrão e bootloaders                                              |
    |        |                                                                         | Leitura: Cap 10.2 Tanenbaum; Kivity et al 2014.                                                                                       |
    | 19/10  | Como tudo isto está organizado em um sistema operacional?               | Aula estúdio para projeto: Linux do Zero                                                                                              |
    | 22/10  | Como tudo isto está organizado em um sistema operacional?               | Aula estúdio para projeto: Linux do Zero                                                                                              |
    | 26/10  | O que é um sistema operacional? Como os programas se comunicam com ele? | Sistemas operacionais: processos. Explorando chamadas de sistemas para entrada/saída                                                  |
    |        |                                                                         | Leitura: Cap 8 CS:APP,                                                                                                                |
    | 29/10  | O que é um sistema operacional? Como os programas se comunicam com ele? | Sistemas operacionais: processos. Explorando chamadas de sistemas para criação de processo (fork) e espera de seus resultados (wait). |
    |        |                                                                         | Leitura: Cap 8 CS:APP,                                                                                                                |
    |        |                                                                         | Leitura complementar sobre escalonamento de processos: Cap 5 Silberschats                                                             |
    | 02/11  | FERIADO                                                                 | PROVA INTERMEDIÁRIA                                                                                                                   |
    | 05/11  | O que é um sistema operacional? Como os programas se comunicam com ele? | Sistemas operacionais: processos. Explorando chamadas de sistemas para execução de programas (exec)                                   |
    |        |                                                                         | Leitura: Cap 8 CS:APP,                                                                                                                |
    | 09/11  | E se o SO quiser avisar um processo que algo ocorreu?                   | Sinais: conceitos, captura e bloqueio.                                                                                                |
    |        |                                                                         | Introdução à ideia de concorrência                                                                                                    |
    | 12/11  | E se o SO quiser avisar um processo que algo ocorreu?                   | Captura e bloqueio de sinais: teoria e exercícios práticos                                                                            |
    | 16/11  | Como envio informações entre processos?                                 | Entrada e saída padrão, chamadas de sistema pipe, dup2 para redirecionamento de arquivos.                                             |
    | 19/11  | É possível dividir o trabalho em partes que executem ao mesmo tempo?    | Introdução ao conceito de threads e sua utilização                                                                                    |
    |        |                                                                         | Criação de threads usando pthreads.                                                                                                   |
    |        |                                                                         | Leitura: Cap 12 CS:APP                                                                                                                |
    | 23/11  | É possível dividir o trabalho em partes que executem ao mesmo tempo?    | Tarefas IO- e CPU-bound. Sincronização usando semáforos.                                                                              |
    |        |                                                                         | Leitura: Cap 12 CS:APP                                                                                                                |
    | 26/11  | PROVA FINAL                                                             | PROVA FINAL                                                                                                                           |
    | 30/11  | PROVA FINAL                                                             | PROVA FINAL                                                                                                                           |
    | 03/12  | nan                                                                     | nan                                                                                                                                   |
    | 07/12  | PROVA SUB                                                               | PROVA SUB                                                                                                                             |

