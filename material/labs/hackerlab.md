# Hackerlab

## Introdução

O propósito desta atividade é torná-los proficientes na engenharia reversa de executáveis. Cada um de vocês recebeu um executável `app` que pede uma série de senhas para ser desativado. Estas senhas devem ser descobertas através da análise do código Assembly do executável.

O seu executável foi deixado no seu repositório de entregas da disciplina. Ao executá-lo, confira se o seu nome é a primeira saída. Em caso negativo, entre em contato com o professor imediatamente.

## Entrega

Você deverá submeter um arquivo contendo as senhas usadas para desativar cada nível. Cada senha deverá estar em uma linha. O arquivo entregue deve funcionar como entrada para liberar acesso à aplicação!

<div class="termy">

```console
$ ./app < solucao.txt
```

</div>

**Atenção**: o arquivo deve se chamar `solucao.txt`, ser editado no Linux e codificado como UTF-8.

Para que sua solução seja considerada pelo servidor de correção, após subir suas alterações, faça uma tag com o padrão de nomenclatura `lab1.x.y`, substituindo `x` e `y` por qualquer número inteiro! Ex:

<div class="termy">

```console
$ git tag -a lab1.0.1 -m "lab1.0.1"
# git push origin lab1.0.1
```

</div>


## Pontuação

São dez níveis e cada um vale **1,0** de nota.

## Prazo

Veja mais em https://insper.github.io/SistemasHardwareSoftware/sobre/