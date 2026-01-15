# Github Password

Caso o seu Github esteja solicitando senha a cada push, você tem duas opções para configurar um esquema de login automático: **chave ssh** ou **token**.

## Chave SSH

Se você costuma clonar os repositórios utilizando **ssh**, acesse [este LINK](https://www.theserverside.com/blog/Coffee-Talk-Java-News-Stories-and-Opinions/GitHub-SSH-Key-Setup-Config-Ubuntu-Linux) e veja como criar uma chave no Ubuntu e adicionar no Github. Após esta configuração, acessos utilizando esta chave serão automaticamente reconhecidos e aceitos como do seu usuário.

## Arquivo `.netrc`

Se você costuma clonar os repositórios utilizando **https**, acesse [este LINK](https://github.com/settings/tokens), na página selecine **Personal access tokens -> Tokens (classic)**. Clique o botão **Generate new token** e escolha **Generate new token (classic)**, de um nome para token na caixa de texto **Note** selecione uma validade adequada (**pelo menos 120 dias**) e marque em **Select scopes** pelo menos a seção `repo.


Em seguida, crie um arquivo `.netrc` (sim, começa com "ponto") na raiz do seu usuário no Ubuntu. O conteúdo deste arquivo deve estar no padrão:

```console
machine github.com login bruna2022 password ghp_123412341234123412341234123412341234
```

!!! example
    Substitua `bruna2022` pelo seu usuário do Github e `ghp_1234*` pelo Token criado.

No terminal, configure as permissões adequadas para o arquivo:

<div class="termy">

```console
$ chmod 600 ~/.netrc
```

</div>

E feito!

[Clique aqui](https://thandang.medium.com/netrc-access-to-git-repo-without-typing-password-any-time-for-macosx-bf37989358e4) para mais informações


