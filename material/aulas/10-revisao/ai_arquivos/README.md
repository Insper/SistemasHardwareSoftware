# Prova Sistemas Hardware Software

### Duração: 180 minutos
### 4 Questões

**ATENÇÃO:** O proctorio estará com tempo superior a 180 minutos, desconsidere.

* Em cada questão é indicado um arquivo para colocar sua resposta.
* Dúvidas dos enunciados da prova serão resolvidos via chat. Fale direto com os professores para não tirar a atenção dos colegas.
* É permitido consultar o material da disciplina durante a prova e materiais, em formato digital ou físico. **Ficam proibidas consultas a materiais de outros alunos ou publicar questões na Internet.**
* A prova é individual. Qualquer consulta a outras pessoas durante a prova constitui violação ao Código de Ética do Insper.
* A prova deve ser um exercício intelectual seu. Fica proibido utilizar calculadora, programas ou qualquer outra ferramenta que resolva para você os exercícios (engenharia reversa ou conversão entre bases). Ex: você pode utilizar a calculadora para fazer operações, mas se utilizar a calculadora para converter automaticamente de uma base para outra, então você estará infringindo as regras.



## Questão 01

Neste exercício você deve realizar conversões entre bases.

**ATENÇÃO**: Neste exercício, fica proibido utilizar qualquer ferramenta (ex: calculadora, programa, site) que realize toda a conversão pra você. É permitido utilizar a calculadora para realizar contas simples (soma, divisão, subtração, etc.), mas lembre-se que a conversão deve ser um exercício intelectual seu!

Passe suas respostas para o arquivo `solucao.txt` e execute com

./q1 < solucao.txt

**Onde deixo minhas respostas?**: no arquivo `solucao.txt`

**Critérios de avaliação**: pelo teste automático, sua nota será a proporção de respostas **corretas**

**Pontos possíveis**: 1,5



## Questão 02

Este exercício contém três funções `func1`, `func2` e `func3`. Cada função recebe um parâmetro, faz algo e então retorna `1` ou `0`.

Seu objetivo é descobrir entradas que fazem as funções `func1`, `func2` e `func3` retornar 1.

Coloque as respostas no arquivo `solucao.txt` e rode

> `./q2 < solucao.txt`

- **Preciso fazer engenharia reversa?** Você vai precisar analisar o assembly para entender as operações envolvidas, mas não precisa entregar esta tradução. Sua entrega deve ser apenas as entradas no arquivo `solucao.txt`.

**Onde deixo minhas respostas?**: no arquivo `solucao.txt`

**Critérios de avaliação**: proporção de respostas **corretas**. Ainda, caso apareça mensagem indicando que travou o software, desconta-se uma resposta correta.

**Pontos possíveis**: 2,5



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
* 50% - passar em todos os testes (sem truques para burlá-los)
* 20% - acertar os tipos das chamadas de função
* 30% - código legível e sem construções estranhas (entregue a melhor versão do seu exercício, se fez if-goto e depois C legível, entregue apenas C legível!)

**Pontos possíveis**: 3,0



## Questão 4

Faça engenharia reversa da função `ex4` contida em `q4.o`.

Coloque sua solução no arquivo `solucao.c`, chamando sua função de `ex4_solucao`.

Para compilar os testes e sua solução use

> `gcc -Og -g -fno-stack-protector solucao.c q4.o -lsystemd -lm -o q4`

Estes exercícios possuem testes automáticos para servir como auxílio.

Observe, nos critérios de avaliação, que acertar o cabeçalho da função e fazer uma versão legível do código também fazem parte da nota. Ainda, neste exercício você precisará tentar entender o que o programa faz. Deixe a sua explicação no arquivo `explicacao.md` dentro da pasta `q4.

Execute os testes automáticos com:
> `./q4`

**Critérios de avaliação**:
* 40% - passar em todos os testes (sem truques para burlá-los)
* 20% - acertar os tipos das chamadas de função
* 30% - código legível e sem construções estranhas (entregue a melhor versão do seu exercício, se fez if-goto e depois C legível, entregue apenas C legível!)
* 10% - explicou corretamente o que o programa faz (preencher arquivo `explicacao.md`).

**Pontos possíveis**: 3,0