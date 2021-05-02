# 15 - Linux do Zero II: processos de usuário e I/O

Agora que já conseguimos criar processos e executar programas vamos adicionar processos de usuários úteis ao nosso sistema da aula 12!

!!! tip "Recapitulação"
    Na aula 12 montamos um sistema de arquivos minimal com apenas um processo (`/hello`) que mostrava uma mensagem de erro e parava. Agora vamos permitir que o usuário execute programas nesse sistema!

## A biblioteca padrão - `libc`

A biblioteca padrão *C* contém uma função em *C* para cada chamada de sistema disponível e interpreta os códigos de erro, deixando-os em um formato (um pouco) mais amigável. Como vimos em aula, realizar chamadas de sistema é uma tarefa que depende do hardware e por isso é diferente em cada arquitetura (ARM vs x86, por exemplo). Logo, a `libc` oferece uma camada de abstração maior acima do sistema operacional, já que programas construídos usando suas função são portáveis em nível de código fonte. Ou seja, necessitando somente a recompilação do executável para funcionar em outras plataformas. Ela também oferece as funcionalidades necessárias para carregar dinamicamente bibliotecas `.so`, como vimos na parte final da aula 12. Por outro lado, além do kernel precisamos portar a `libc` também cada vez que trabalhamos com arquiteturas novas.

Neste exemplo iremos usar a `glibc`, implementação feita pela GNU e usada na maioria das distribuições. Desta vez não precisamos compilar nada: ela já está instalada no nosso sistema e podemos simplesmente usá-la na próxima parte.

## Ferramentas de modo usuário - `busybox`

Agora que já temos uma interface com o kernel via `glibc` precisamos de programas básicos para utilizar nosso sistema. Estamos falando de programas como `cp`, `ls` e até mesmo o nosso shell (`bash`). Assim como o kernel e a libc, o padrão *POSIX* também diz como esses programas deverão funcionar, fazendo com que sua utilização básica seja igual em qualquer sistema compatível. Lembre-se que o kernel não faz nada, ele apenas *intermedia* o acesso ao hardware. Precisamos então de programas que irão tornar esse hardware útil.

O *busybox*([https://busybox.net/about.html](https://busybox.net/about.html)) é um conjunto de ferramentas modo usuário bastante compacto e rápido. Ele contém implementações leves dos executáveis `ash` (shell leve alternativo ao `bash`), `ls`, `vi`, `pwd`, etc. Sua vantagem é o baixo consumo de memória e seu tamanho pequeno após compilado. É muito usado em sistemas embarcados.

Vamos começar baixando os fontes da versão `1.32.1`. A compilação é feita no mesmo esquema do kernel:

```
$> make defconfig
$> make menuconfig
```

!!! question medium
    O busy box disponibiliza um grande número de ferramentas. Procure no menu acima o lugar onde são listados os editores de texto disponíveis no *busybox*.

Desta vez iremos fazer uma modificação nas configurações padrão. Como queremos que esses executáveis pequenos, muito rápidos e que rodem sem qualquer outro tipo de serviço carregado no sistema, iremos compilá-los **estaticamente**.

!!! example
    Procure a opção para lincar o `busybox`estaticamente (Submenu *Settings*), habilite-a e faça a compilação.

    ```
    $> make -j8
    ```

!!! example
    Cheque que seu executável `busybox` realmente não tem dependências usando o comando `ldd`.

Isto demorará bem menos que a compilação do kernel e pode ser feito enquanto outras coisas acontecem. Após a compilação um executável `busybox` deverá ter sido gerado na pasta *busybox-1.32.1*.

O `busybox` inclui, em um só executável, todas ferramentas listadas acima. Para executá-las basta passar o nome da ferramenta escolhida como argumento. Veja o exemplo abaixo.

```
$> ./busybox ls
```

Se tudo funcionou igual ao `ls` padrão de seu sistema então passe para o próximo passo.

!!! example
    Execute `busybox ls --help`. Compare a saída com `ls --help`. Existe diferença? Procure na saída do `ls` do seu sistema qual a implementação utilizada.

!!! example
    Você pode obter uma lista completa de todas as ferramentas que o busybox oferece executando `busybox --list-full`. Execute o comando e interprete sua saída. Esses comandos estão disponíveis no seu sistema atual?

Usar as utilidades do `busybox` como mostrado acima não é muito prático. Por isso ele oferece a possibilidade de ser chamado de uma maneira diferente. Vejamos abaixo:

!!! example
    Vamos primeiro criar um link simbólico de `busybox` para o nome `ls`:

    `ln -s ./busybox ./ls`

!!! tip "Um link simbólico é um novo nome para um arquivo. Ambos apontam para o mesmo dado no disco, mas possivelmente em caminhos distintos no sistema."

!!! example
    Execute `./ls` e veja o que acontece.

Tanto `./ls` quanto `./busybox` apontam para os mesmos dados no disco, porém o `busybox` é programado para checar `argv[0]` ao iniciar. Ou seja, se ele for chamado com `argv[0]` igual a `"ls"` essa ferramenta já é executada automaticamente! Podemos criar links simbólicos para todas as ferramentas listadas nas tarefas anteriores e usá-las diretamente! Faremos isso mais para frente.



## Organizando nossos dados

!!! example
    Verifique que seu sistema contém todas as pastas da *Tarefa 22* da aula 12.

!!! tip "Para as próximas tarefas você precisará da sua imagem de disco montada em `raiz_linux` novamente. Não se lembra como fazer isso? Volte na aula 12 e reveja."

!!! example
    Dê permissões totais para a pasta `tmp` e somente para o usuário dono na pasta `root`.

    ```
    #> chmod 777 tmp
    #> chmod 600 root
    ```

!!! example
    Copie o executável do *busybox* para a pasta `raiz_linux/usr/bin`.


!!! example
    Execute o comando abaixo na dentro de `raiz_linux/`.

    ```
    for util in $(./usr/bin/busybox --list-full); do
     ln -s /usr/bin/busybox $util
    done
    ```

Agora criamos links simbólicos de todas as ferramentas de usuário mais comuns e já conseguiremos usar nosso sistema!

## Um segundo boot

Vamos agora usar essas ferramentas de usuário em nosso sistema. Elas já estão nos lugares corretos (`/bin/` para os utilitários padrão e `/sbin` para os utilitários de administração), então poderemos usá-los diretamente no nosso sistema Linux. 

!!! tip "Não se esqueça de `umount` sua imagem antes de fazer o boot."

!!! example
    Realize novamente o boot com o `qemu`, mas desta vez use `init=/bin/ash`. Ou seja, o primeiro processo de usuário agora será um shell que nos permitirá executar comandos no nosso sistema.

!!! question medium
    Tente fazer as seguintes operações no seu sistema:

    1. mudar de diretórios com  `cd`
    2. listas conteúdos das pastas com `ls`
    3. criar arquivos no disco com `touch` ou `vi`
    4. mostrar espaço livre no disco com `df`
    5. listar hardware disponível com `lspci`

    Anote quais funcionaram e, se der erro, anote o erro.

!!! progress
    Clique aqui após tentar as operações acima

Você deve ter notado que não foi possível nem criar arquivos nem executar os comandos `df` e `lspci`. Isso ocorre pois não **inicializamos o sistema de entrada e saída de nosso Linux**. Ou seja, não cumprimos todas as etapas necessárias para que os programas de usuário possam se comunicar com o kernel.

Vamos fazer isso manualmente hoje e, em uma próxima atividade, iremos completar a inicialização do nosso sistema.

!!! example short
    O sistema de arquivos carregado inicialmente pelo kernel é montado em modo *somente leitura*. Pesquise como *remontar* um sistema de arquivos para *leitura e escrita* e escreva o comando abaixo.

    !!! details "Resposta"
        `mount -o remount,rw /`

Os sistemas de arquivos `proc` e `sys` expõem informações do kernel a processos de usuário e são essenciais para o funcionamento de diversos programas. Eles são criados em tempo de execução usando o comando `mount`

!!! example
    Rode os seguintes comandos e verifique que agora `df` e `lspci` funcionam corretamente.

    ```
    #> mount -t proc proc /proc -o nosuid,noexec,nodev
    #> mount -t sysfs sys /sys -o nosuid,noexec,nodev
    ```

Vamos explorar um pouco o diretório `/proc`:

!!! question short
    Entre em `/proc` e procure por um arquivo que possa conter informações sobre a CPU atual. Anote seu nome abaixo e mostre seu conteúdo no terminal usando `cat`

    !!! details
        `/proc/cpuinfo`


!!! question short
    Que outras informações você pode obter em `/proc`? Liste algumas abaixo.

Agora que conseguimos configurar uma parte minimal de nosso sistema vários dos comandos já devem estar plenamente funcionais. Porém, note que fizemos essas alterações manualmente. Logo, ao reiniciarmos teremos que fazer tudo isso novamente!. 

## Sistema de inicialização

O *busybox* já nos fornece um sistema de inicialização minimal que, entre outras coisas, rodaria estes comandos automaticamente a todo boot. Aproveitaremos ele para três propósitos:

1. executar um script de inicialização que configure todos os diretórios especiais e serviços.
1. adicionar serviços que proveem uma tela de login
1. executar um script de finalização que desliga o hardware quando o PC for desligado.

Primeiro vamos copiar versões padrão de todos os arquivos de configuração necessários. Os seguintes arquivos estão na pasta `configs` do repositório da aula.

* `passwd, shadow, groups`: listam os usuários e grupos presentes. `shadows` contém hashes das senhas.
* `profile`: é executado logo após um login correto. Pode ser usado para configurar o terminal.
* `issue`: contém o nome do seu sistema mostrado na tela de login.
* `hosts`: associa um nome com alguns IPs. É aqui que associamos *localhost* a `127.0.0.1`
* `hostname`: configura o nome da nossa máquina na rede.
* `fstab`: lista todos os discos que devem ser montados além do *rootfs*.

!!! example
    Copie estes arquivos para o `etc` do seu sistema.

O sistema de `init` disponibilizado pelo *busybox* lê o arquivo `/etc/inittab` e o interpreta de acordo com as regras mostradas no arquivo *busybox-1.30.1/examples/inittab*. Iremos usar o arquivo disponível em `configs/inittab`.

!!! question
    Leia o arquivo `config/inittab` e tente interpretar seu conteúdo.

A primeira coluna do arquivo mostra o momento em que ela deve rodar. Vemos, por exemplo, que o script `/etc/init.d/startup` rodará ao inicializar o sistema e que toda vez que o processo `/sbin/getty` (terminal com login) terminar ele é reiniciado. Também existem scripts para serem rodados ao desligar o sistema.

Em especial, este arquivo `/etc/init.d/startup` (presente no repositório como `configs/init.d/startup`) contém comandos para configurar o sistema, incluindo os diretórios especiais que mostramos acima. Seu conteúdo é mostrado abaixo por completude.

```shell
# Monta os sistemas de arquivos especiais
mount -t proc proc /proc -o nosuid,noexec,nodev
mount -t sysfs sys /sys -o nosuid,noexec,nodev

# Configura detector de dispositivos
mkdir -p /dev/pts /dev/shm
mount -t tmpfs shm /dev/shm -o mode=1777,nosuid,nodev
mdev -s
echo /sbin/mdev > /proc/sys/kernel/hotplug

# Configura terminais
mount -t devpts devpts /dev/pts -o mode=0620,gid=5,nosuid,noexec

# Configura /run, que guarda algumas informações de execução.
mount -t tmpfs run /run -o mode=0755,nosuid,nodev

# Atribui nome ao PC
cat /etc/hostname > /proc/sys/kernel/hostname

# Monta todos os sistemas de arquivos contidos em /etc/fstab
mount -a

mount -o remount,rw /
```

!!! warning
    Não se esqueça de dar permissões de execução para `/etc/init.d/startup`.

!!! example
    Este script requer a criação de um diretório `/run`. Para que ele serve? Crie-o e copie ambos arquivos acima para seu sistema.

Agora vamos rodar de novo, desta vez com nosso novo sistema de inicialização configurado.

!!! example
    Modifique sua linha de comando do *QEmu* e retire a porção `init=/bin/sh`. Por padrão o kernel buscará o executável `/sbin/init`, que usará os arquivos que criamos para inicializar o sistema.

!!! tip
    Se tudo deu certo você deverá ter um prompt de login. Logue como *root* e continue o roteiro.

!!! warning
    Não se esqueça de usar `umount` para desmontar a pasta `raiz_linux`.

!!! example
    Crie um arquivo dentro de seu sistema. Você pode usar o editor `vi` ou o comando `touch` para criar um arquivo vazio. Se não deu certo revise se ocorreu tudo certo na execução do seu script `startup` rolando a tela para cima com `Shift+PageUp`.

!!! example
    Desligue seu sistema com `poweroff`. Ligue-o novamente e confira se o arquivo ainda está lá.


