# Hackerlab

## Introdução

O propósito desta atividade é torná-los proficientes na **engenharia reversa de executáveis**. Cada um de vocês recebeu um executável `app` que pede uma série de **senhas** para ser desativado. Estas senhas devem ser descobertas através da análise do código Assembly do executável.

## Onde trabalhar?

O seu executável `app` foi deixado no seu repositório de entregas da disciplina na pasta `lab/01-hackerlab`. Ao executá-lo, confira se o seu nome é a primeira saída. Em caso negativo, entre em contato com o professor imediatamente.

## Como trabalhar?

Execute o `app`. Será apresentado seu nome. Então, o programa irá esperar uma entrada, que é uma senha que destrava o level 1.

<div class="termy">

```console
$ ./app
FABIO
Level1:
```

</div>
<br>

Para descrobrir a senha, você terá que abrir o `app` no `gdb` e fazer engenharia reversa para entender seu código. Quando você tiver descoberto uma senha que destrava o nível, teste se funciona! Vamos supor que você desconfia que a senha seja `lasanha`. 

<div class="termy">

```console
$ ./app
FABIO
Level1:lasanha
Nao foi desta vez!
```

</div>
<br>

Como podemos ver, `lasanha` não é uma senha correta para o nível 1!

Conforme for descobrindo, você deverá editar um arquivo `solucao.txt` contendo as senhas usadas para desativar cada nível. Cada senha deverá estar em uma linha. O arquivo entregue deve funcionar como entrada para liberar acesso à aplicação!

<div class="termy">

```console
$ ./app < solucao.txt
```

</div>
<br>

!!! warning "Atenção!"
    O arquivo deve se chamar `solucao.txt`, ser editado no Linux e codificado como UTF-8.

## Como entregar?

Para que sua solução seja considerada pelo servidor de correção, **suba suas alterações para o github**

<div class="termy">

```console
$ git add .
$ git -m commit "lab1"
$ git push
```
</div>
<br>

**Faça uma tag com o padrão de nomenclatura `lab1.x.y`**, substituindo `x` e `y` por qualquer número inteiro! Ex:

<div class="termy">

```console
$ git tag -a lab1.0.1 -m "lab1.0.1"
$ git push origin lab1.0.1
```

</div>
<br>

!!! note "Entregas contínuas!"
    Não deixe para entregar no último minuto, faça entregas contínuas conforme for evoluindo nos níveis!

    Além disso, comece **logo**. O lab foi pensado para ser feito conforme os conteúdos são apresentados. Certamente terá dificuldades se deixar para os últimos dias!

## Como serei avaliado?

São dez níveis e cada um vale **1,0** de nota. Sua solução conseguirá ficar com status **^^pass^^** apenas quando conseguir passar em todos os níveis, e sua nota será `10,0`, e o SVG no seu repositório ficará **^^verde^^**. Em caso de  **$\color{red}{\textsf{fail}}$** a nota parcial será considerada, para saber sua nota acesse a última `issues` gerada no repositório referente ao lab.

## Qual o prazo?

Veja mais em https://insper.github.io/SistemasHardwareSoftware/entregas/