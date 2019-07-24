% Atividade 01 - números na CPU
% Igor Montagner
% Sistemas Hardware-Software 2019/2

# Parte 1 - inteiros

Trabalharemos primeiro com inteiros com e sem sinal. 

**Exercício 1**: complete a tabela abaixo. O tipo de dado usado é `unsigned char` (inteiro sem sinal de 8 bits).

Decimal       Binário        Hexadecimal
-------       ---------      -----------
197                          
              1101 1001      
                             0xAD
              1001 1011      
48                           
              1111 0110      
                             0x15


**Exercício 2**: Complete a tabela abaixo. O tipo de dado usado é `char` (inteiro com sinal de 8 bits). 

Decimal       Binário        Hexadecimal
-------       ---------      -----------
-22                         
              1010 1001      
                             0xBB
              1011 1100      
-119                         
                             0xD4
                             
**Exercício 3**: Vamos agora trabalhar com conversões entre inteiros com e sem sinal. Complete a tabela abaixo considerando inteiros de 8 bits. 

Com Sinal    Binário      Sem Sinal
---------    ---------    ----------
-78                       
             1001 0101     
                          167
             1111 1111

# Parte 2 - fracionários

Nesta parte trabalharemos com o padrão IEEE 754 apresentado em sala de aula. 

**Exercício 4**: Converta os números fracionários abaixo para decimal. Coloque na primeira coluna (*Mantissa$\times$Expoente*) o número fracionário
escrito em binário, mas com a vírgula já corretamente posicionada. Em seguida preencha as duas colunas seguintes com a parte inteira e 
a parte fracionária escritas em decimal. 

Notação científica binária          Mantissa$\times$Expoente       Parte inteira      Parte fracionária
------------------------------      ------------------------       -------------      -------------
$-1 \times 1.11001 \times 2^1$     
$1 \times 1.1011 \times 2^{-2}$   
$-1 \times 1.101 \times 2^{3}$ 
$1 \times 1.110101 \times 2^{7}$
$1 \times 1.110101 \times 2^{0}$
-------------------------------

Agora faremos o caminho oposto: converteremos números fracionários em base 10 para o padrão IEE 754. Isto será feito em várias etapas nos próximos exercícios.

**Importante**: muitos números decimais fracionários não possuem uma representação exata em binário. Por isso vamos nos limitar a usar até 4 casas fracionárias nos exercícios abaixo, sempre aproximando o número por baixo.

**Exercício 5**: Para cada número fracionário em base 10 abaixo, preencha as colunas *Parte Inteira* e *Parte Fracionária* com as representações em binário dessas partes. 

Decimal                Sinal         Parte Inteira           Parte fracionária
-------                -----         -------------           -----------------
-658,75
125,8
-2048
0,3465
-----------

**Exercício 6**: Com os dados acima em mãos, preencha as colunas abaixo com a Mantissa (em binário), o Expoente (em decimal) e o Expoente levando em conta *bias* para o tipo `float`. 

**Importante:** você não deve incluir o **1** implícito na mantissa. 

Decimal                  Mantissa          Expoente         Expoente (float)
-------                  --------          --------         ----------------
-658,75
125,8
-2048
0,3465
-----------

**Exercício 7**: Ao nos limitarmos a 5 casas decimais estamos incluindo um erro em nossa representação. Escreva abaixo o número representado e o a diferença para o número fracionário original. 

Original       Número representado        Erro
----------     -------------------        -----
-658,75
125,8
-2048
0,3465
------

