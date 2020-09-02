# 99 - Corretor Automático

Algumas atividades de sala de aula entrarão na nota final. Elas estão marcadas como **Entrega** no início e serão entregues via um repositório especial no Github.

1. Preencha a pesquisa de usuários do Github

<iframe width="640px" height= "480px" src= "https://forms.office.com/Pages/ResponsePage.aspx?id=wKZwY5B7CUe9blnCjt6DOy1oY8Gb_ghOlbw3-aL0eF5UMTZONERZTEFPVEdQUERaSFdZQURQWEsyTCQlQCN0PWcu&embed=true" frameborder= "0" marginwidth= "0" marginheight= "0" style= "border: none; max-width:100%; max-height:100vh" allowfullscreen webkitallowfullscreen mozallowfullscreen msallowfullscreen> </iframe>

2. Você receberá um convite para repositório. Todas as atividades serão disponibilizadas neste repositório e suas soluções devem ser adicionadas nos arquivos correspondentes. 
3. O corretor automático depende do pacote `grading-tools`, que deverá ser instalado como abaixo.

```shell
$> python3.8 -m pip install --user git+https://github.com/igordsm/grading-tools
```

??? tip "Python 3.8 no Ubuntu"
    Se seu `python3` é uma versão inferior ao 3.8, você pode instalá-lo com os pacotes abaixo:

    ```
    python3.8 python3.8-dev 
    ``` 

    A partir daí poderá seguir normalmente as instruções desta página.

4. Com isso configurado, é só compilar seu programa e rodar `python3.8 corretor.py executavel`. 
5. Para baixar os novos exercícios é só rodar `git pull`. 
6. Os exercícios serão entregues criando um commit com sua resposta e dando `git push`. 

!!! warning
    Fique atento a atualizações no seu repositório de atividades. Todo novo exercício para entrega disponibilizado nos handouts devera aparecer no seu repositório também. Será avisado em aula se for necessário atualizar também o pacote acima.
