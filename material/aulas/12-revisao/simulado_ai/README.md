# Prova Sistemas Hardware Software

<!-- markdown_py README.md > README.html -->

### Duração: 180 minutos
### 5 Questões

**ATENÇÃO:** O proctorio estará com tempo superior a 180 minutos, desconsidere.

* Em cada questão é indicado um arquivo para colocar sua resposta.
* É permitido consultar o material da disciplina durante a prova (repositório da disciplina  eseu repositório de atividades), além de seus materiais físicos, a calculadora nativa do Ubuntu e os links de sites presentes nas aulas, tais como: https://godbolt.org/, https://sourceware.org/gdb/onlinedocs/gdb/index.html, https://software.intel.com/en-us/articles/intel-sdm. **Ficam proibidas consultas a materiais de outros alunos ou pesquisas na Internet.**
* Fica proibido o uso de ferramentas de IA ou auto-complete
* A prova é individual. Qualquer consulta a outras pessoas durante a prova constitui violação ao Código de Ética do Insper. Não abra E-mail, Whatsapp, Discord, etc.
* A prova deve ser um exercício intelectual seu. Fica proibido utilizar programas ou qualquer outra ferramenta que resolva para você os exercícios (engenharia reversa).
* Fica proibido o uso de ferramentas de geração de código como o copilot. Sujeito a código de ética.

## Instalação

Se receber reclamações como `cannot find -lsystemd`, instale com:

`sudo apt update`

`sudo apt install build-essential libsystemd-dev`

## Questão 01

Se não conseguir rodar o executável `./q1`, execute o comando:

`chmod +x q1`

Neste exercício, você deve responder `V` ou `F` para as afirmações retornadas.

Passe suas respostas para o arquivo `solucao.txt` e execute com

./q1 < solucao.txt

**Onde deixo minhas respostas?**: no arquivo `solucao.txt`

**Critérios de avaliação**: sua nota será a proporção de respostas **corretas** (por motivos óbvios, correção posterior a prova)

**Pontos possíveis**: 1,0


## Questão 02

Se não conseguir rodar o executável `./q2`, execute o comando:

`chmod +x q2`

Este exercício é um mini **HackerLab**. Utilize seus conhecimentos adquiridos para descobrir a senha de cada nível!

Coloque as respostas no arquivo `solucao.txt` e rode

> `./q2 < solucao.txt`

- **Preciso fazer engenharia reversa?** Você vai precisar analisar o assembly para entender as operações envolvidas, mas não precisa entregar esta tradução. Sua entrega deve ser apenas as entradas no arquivo `solucao.txt`.

**Onde deixo minhas respostas?**: no arquivo `solucao.txt`

**Critérios de avaliação**: A nota será disponibilizada na saída padrão!

**Pontos possíveis**: 2,0


## Questão 3

Faça engenharia reversa das funções `ex3` continda em `q3.o`.

Coloque sua solução no arquivo `solucao.c`, chamando sua função de `ex3_solucao`.

Para compilar os testes e sua solução use

> `gcc -Og -g -fno-stack-protector solucao.c q3.o -lsystemd -lm -o q3`

Este exercício possui testes automáticos para servir como auxílio.

Execute os testes automáticos com:
> `./q3`

Observe, nos critérios de avaliação, que acertar o cabeçalho da função e fazer uma versão legível do código também fazem parte da nota.

**Critérios de avaliação**:
* 50% - pela proporção de testes com PASS (sem truques para burlá-los)
* 20% - acertar os tipos das chamadas de função
* 30% - código legível e sem construções estranhas (entregue a melhor versão do seu exercício, se fez if-goto e depois C legível, entregue apenas C legível!)

**Pontos possíveis**: 2,0

## Questão 4

Faça engenharia reversa da função `ex4` contida em `q4.o`.

Coloque sua solução no arquivo `solucao.c`, chamando sua função de `ex4_solucao`.

Para compilar os testes e sua solução use

> `gcc -Og -g -fno-stack-protector solucao.c q4.o -lsystemd -lm -o q4`

Este exercício possui testes automáticos para servir como auxílio.

Observe, nos critérios de avaliação, que acertar o cabeçalho da função e fazer uma versão legível do código também fazem parte da nota. Ainda, neste exercício você precisará tentar entender o que o programa faz. Deixe a sua explicação no arquivo `explicacao.md` dentro da pasta `q4.

Execute os testes automáticos com:
> `./q4`

**Critérios de avaliação**:
* 40% - pela proporção de testes com PASS (sem truques para burlá-los)
* 20% - acertar os tipos das chamadas de função
* 30% - código legível e sem construções estranhas (entregue a melhor versão do seu exercício, se fez if-goto e depois C legível, entregue apenas C legível!)
* 10% - explicou corretamente o que o programa faz (preencher arquivo `explicacao.md`).

**Pontos possíveis**: 3,0


## Questão 5

Neste exercício seu trabalho será criar uma função

```
char *extrair_arquivo(char *url)
```

que analisa a string `url` e retorna um ponteiro para **UMA NOVA string**, alocada **dinamicamente** contendo:

- O nome do arquivo apontado pela URL.

Exemplos:

- Para a entrada **http://www.google.com/icon.png** você deve retornar um `char*` contendo **icon.png**

- Para a entrada **ftp://receita.fazenda.gov.br/ir/2022/report1.pdf** você deve retornar um `char*` contendo **report1.pdf**

Abra o arquivo `extrair.c`, e implemente a função acima. Sua nota será pela porcentagem de testes aprovados, considerando um total de quatro testes.

Para compilar:

```
gcc -Og -g q5.o extrair.c -o q5
```

Para rodar os testes automáticos:

```
./q5
```

**OBS**:

- É proibido utilizar funções da `string.h`. Ex: strlen, strcpy, strrchr, etc. Se utilizar, a questão será zerada.

- Precisa funcionar para qualquer URL, se tiver testes fixos apenas para burlar os testes, irá zerar!

- Nota conforme proporção dos testes aprovados. Se tiver algum erro no valgrind, a questão terá um desconto de 50%.


**Pontos possíveis**: 2,0