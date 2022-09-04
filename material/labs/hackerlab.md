# Hackerlab

## Introdução

O propósito desta atividade é torná-los proficientes na engenharia reversa de executáveis. Cada um de vocês recebeu um executável `app` que pede uma série de senhas para ser desativado. Estas senhas devem ser descobertas através da análise do código Assembly do executável.

## Onde trabalhar?

O seu executável `app` foi deixado no seu repositório de entregas da disciplina na pasta `lab/01-hackerlab`. Ao executá-lo, confira se o seu nome é a primeira saída. Em caso negativo, entre em contato com o professor imediatamente.

## Como trabalhar?

Você deverá editar um arquivo `solucao.txt` contendo as senhas usadas para desativar cada nível. Cada senha deverá estar em uma linha. O arquivo entregue deve funcionar como entrada para liberar acesso à aplicação!

<div class="termy">

```console
$ ./app < solucao.txt
```

</div>

!!! warning "Atenção!"
    O arquivo deve se chamar `solucao.txt`, ser editado no Linux e codificado como UTF-8.

!!! tip "Dica de trabalho!"
    Para não ter que redigitar todas as senhas, você pode trabalhar direto no `solucao.txt` e, enquanto não finaliza todos os níveis, deixe uma a linha a mais propositalmente preenchida com algum lixo (ex: um inteiro), assim conseguirá testar cada nível sempre com `./app < solucao.txt`!


Para que sua solução seja considerada pelo servidor de correção, após subir suas alterações, faça uma tag com o padrão de nomenclatura `lab1.x.y`, substituindo `x` e `y` por qualquer número inteiro! Ex:

<div class="termy">

```console
$ git tag -a lab1.0.1 -m "lab1.0.1"
$ git push origin lab1.0.1
```

</div>


## Pontuação

São dez níveis e cada um vale **1,0** de nota. Sua solução conseguirá ficar com status `pass` apenas quando conseguir passar em todos os níveis, entretanto, mesmo com `fail` a nota parcial será considerada.

## Prazo

Veja mais em https://insper.github.io/SistemasHardwareSoftware/sobre/