# 13 - Linux do Zero

## Tarefas preliminares

Vamos precisar dos seguintes softwares instalados no sistema. Como o resto do curso, os pacotes abaixo são para o Ubuntu 22.04 LTS.

<div class="termy">

    ```console
    $ sudo apt install build-essential flex bison qemu ncurses-dev libssl-dev libelf-dev qemu-system-x86
    ```

</div>


!!! example "Faça!"
    Instale os pacotes acima no seu sistema.

!!! warning "Atenção!"
    Este roteiro precisa ser feito com **atenção**! Procure ler bem todos os passos e resolver tentando entender o que está acontecendo.

## Compilando o kernel

Vamos primeiro fazer o download do kernel do Linux no [site oficial](https://www.kernel.org/)([https://www.kernel.org/](https://www.kernel.org/)). Podem baixar a versão estável mais recente (atualmente`6.2.10`)

!!! warning "Pasta para aula"
    Crie uma pasta para a aula de hoje e faça tudo dentro desta pasta.

!!! example
    Decompacte o arquivo baixado e examine os arquivos na pasta criada.

    <div class="termy">

    ```console
    $ tar xvf linux-X.Y.Z.tar.xz
    ```

    </div>

Isto criará uma pasta `linux-X.Y.Z` que contém os fontes de todo o kernel. O kernel pode ser compilado com uma quantidade enorme de configurações diferentes, sendo que a configuração atual é salva no arquivo `.config` dentro da pasta do código fonte.

!!! example "Setar configuração padrão"
    Para definir que o kernel será compilado com as opções padrão, usamos o  comando.

    <div class="termy">

    ```console
    $ make defconfig
    ```

    </div>

!!! example "Personalizar configuração"
    Podemos customizar as configurações disponíveis usando o comando abaixo. Execute-o e explore um pouco as possibilidades.

    <div class="termy">

    ```console
    $ make menuconfig
    ```

    </div>

!!! example "Faça!"
    Encontre a opção *Linux guest support* dentro de *Processor Type and Features*. Se não estiver habilitada, habilite!

!!! example "Compile o kernel!"
    Para compilar seu kernel, execute:

    <div class="termy">

    ```console
    $ make -j8
    ```

    </div>

O exercício acima demora em torno de 10~20 minutos. Enquanto ele acontece, siga a próxima seção.

## A biblioteca padrão - `libc`

A biblioteca padrão *C* é contém uma função em *C* para cada chamada de sistema disponível e interpreta os códigos de erro, deixando-os em um formato (um pouco) mais amigável. Como vimos em aula, realizar chamadas de sistema é uma tarefa que depende do hardware e por isso é diferente em cada arquitetura (ARM vs x86, por exemplo). Logo, a `libc` oferece uma camada de abstração maior acima do sistema operacional, já que programas construídos usando suas função são portáveis em nível de código fonte. Ou seja, necessitando somente a recompilação do executável para funcionar em outras plataformas. Ela também oferece as funcionalidades necessárias para carregar dinamicamente bibliotecas `.so`, como vimos na aula 11. Por outro lado, além do kernel precisamos portar a `libc` também cada vez que trabalhamos com arquiteturas novas.

Neste exemplo iremos usar a `glibc`, implementação feita pela GNU e usada na maioria das distribuições. Desta vez não precisamos compilar nada: ela já está instalada no nosso sistema e podemos simplesmente usá-la na próxima parte.

## Nosso primeiro programa - Hello Linux

!!! example "Crie um programa do zero"
    Crie um programa que mostra a mensagem *Hello Linux (seu nome)*.

Para compilar nosso programa vamos usar a flag especial `-static`. Ao habilitá-la criaremos um executável totalmente autocontido, que pode ser executado sem nenhuma dependência.

!!! example "Compile com `-static`"
    Compile o programa usando o comando abaixo.

    <div class="termy">

    ```console
    $ gcc -Og -Wall -static hello_linux.c -o hello
    ```

    </div>

    Execute-o e veja que tudo funciona normalmente.

Bom, não vemos nenhuma diferença com o comportamento usual. Vamos então aprender a listas as dependências de executáveis.

!!! example "Compile sem `-static`"
    Compile seu programa "normalmente" (sem `-static`) e chame-o de `hello-dyn`.

Podemos checar quais são as dependências de um executável com o comando `ldd`.

!!! example "Conferindo dependências"
    Execute o seguinte comando e veja sua saída:

    <div class="termy">

    ```console
    $ ldd ./hello-dyn
    ```

    </div>

!!! example "Conferindo dependências"
    Execute `ldd` no arquivo `hello` (compilado com `static`) e veja sua saída:

    <div class="termy">

    ```console
    $ ldd ./hello
    ```

    </div>

No primeiro caso deverão ter aparecido alguns arquivos listados como dependências, enquanto no segundo a saída deverá ser vazia. Antes de rodar `hello-dyn` o Linux garante que todos os arquivos listados no exercício anterior estão carregados na memória também. Por esta razão, cada arquivo `.so` listado é chamado de **dependência** de `hello-dyn`.

!!! tip "Confira"
    Agora seu sistema já deve ter acabado de compilar o kernel.

    Verifique que foi criado o arquivo `bzImage` na pasta `linux-X.Y.Z/arch/x86_64/boot/`. Este é o arquivo executável contendo o kernel Linux que compilamos.

    

## Sistema de Arquivos e discos virtuais

Agora que já temos um kernel e um programa que será rodado pelo nosso sistema, vamos criar a primeira versão do disco de nosso sistema. Nossa primeira organização do sistema será incrivelmente minimal e rudimentar. Nosso sistema disco conterá apenas um arquivo: o executável `hello` criado no item anterior.

Vamos começar criando um arquivo vazio de *100Mb* que será usado como nosso diretório raiz `/`.

!!! example
    Crie um arquivo

    <div class="termy">

    ```console
    $ dd if=/dev/zero of=raiz.img bs=1M count=100
    ```

    </div>


Antes de continuar, precisamos expor o arquivo acima como um dispositivo de armazenamento para o restante do sistema. Podemos fazer isto usando um *loopback device*. Este tipo de dispositivo se comporta igual a um disco físico, mas modifica os bytes de um arquivo ao invés de interagir com hardware. O comando `losetup` é usado para fazer este serviço.

<div class="termy">

```console
$ sudo losetup -P -f --show raiz.img
```

</div>


!!! tip
    O comando acima mostra o número do dispositivo criado. Anota para os próximos passos!

    Exemplo: `/dev/loop25`

    Caso se esqueça dele, basta executar `losetup` para listar todos os *loopback devices*.


Agora podemos criar uma *tabela de partições*. Esta estrutura, gravada no começo de um disco, contém informações que permitem identificar quais *partições* estão presentes, seus tamanhos e tipo. Em sua essência, uma *partição* é somente uma subdivisão de um disco físico. Isto ajuda, por exemplo, a instalar vários SOs no mesmo disco sem precisar ter um disco separado para cada sistema. Fazemos tudo isto usando o comando `fdisk`:

!!! tip
    Substitua `/dev/loopXX` pelo caminho retornado quando executou `losetup`!

<div class="termy">

```console
$ sudo fdisk /dev/loopXX
```

</div>


O `fdisk` trabalha como um prompt de comandos. Digite `m` para conhecer as opções.

!!! example
    Crie uma partição (comando `n`) neste disco ocupando todo o espaço disponível. As opções padrão do comando de criar partições são adequadas para nosso uso (leia e dê ENTER em tudo).

!!! example
    Use o comando `p` para mostrar o estado atual do disco. Certifique-se de que há uma partição do tipo *Linux* que ocupe o disco todo. Anote o valor do campo *Disk Identifier*.

!!! tip "*Disk Identifier*"
    O *Disk Identifier* será utilizado sem o `0x` nos próximos passos.

!!! warning "Lembre de salvar!"
    Não se esqueça de usar o comando `w` para salvar as partições criadas antes de sair. Caso contrário, terá que refazer!

!!! warning
    Em Linux um arquivo é simplesmente uma sequência de bytes. Se eu pedir para o sistema interpretar esta sequência como um disco formatado no padrão *ext4* isto terá o mesmo efeito que se essa sequência de bytes estivesse armazenada diretamente em um disco físico.


A partir de agora, o dispositivo */dev/loopXX* (ou algo similar que tenha sido retornado pelo comando acima) é equivalente a um disco físico. Assim como localizamos a primeira partição de um disco usando `/dev/sda1`, localizamos a primeira partição do nosso *loop device* usando `/dev/loopXXp1`.

!!! warning "Confira com cuidado..."
    Se você só tem `/dev/loopXX/` e não possui `/dev/loopXXp1` então houve algo errado com a criação das partições de seu disco. Refaça tudo a partir do comando `dd`.

!!! example "Formatar"
    Vamos agora formatar essa partição e montá-la no diretório *raiz_linux*.

    <div class="termy">

    ```console
    $ sudo mkfs.ext4 /dev/loopXXp1
    $ sudo mkdir raiz_linux
    $ sudo mount -t ext4 /dev/loopXXp1 raiz_linux
    ```

    </div>

Tudo o que for escrito na pasta *raiz_linux* será escrito diretamente no nosso arquivo *raiz.img* da mesma maneira que seria escrito em um disco físico. No nosso caso, tudo o que for colocado nesta pasta estará presente no diretório `/` do nosso sistema Linux.

!!! example
    Copie seu executável `hello` para o nosso disco virtual montado em `raiz_linux`.

    <div class="termy">

    ```console
    $ sudo cp hello raiz_linux/
    ```

    </div>

# Seu primeiro boot

Com isto já temos o mínimo necessário para dar *boot* no sistema, mas não teremos um sistema completamente funcional nem bem montado. Na verdade, nosso SO agora é completamente capenga e tem um zilhão de problema.

A instalação de um *boot loader* é trabalhosa e cheia de possibilidades de erros. Podemos aproveitar o fato do próprio *QEmu* servir de *boot loader* para facilitar o desenvolvimento deste roteiro.

!!! warning
    Antes de usar `qemu` não se esqueça de desvincular `/dev/loopXXp1` de `raiz_linux` usando `umount`.

    <div class="termy">

    ```console
    $ sudo umount raiz_linux
    ```

    </div>

!!! tip
    Você pode checar os discos que estão montados no momento usando o comando `lsblk`

Nosso comando de boot terá o formato abaixo:

```
$ sudo qemu-system-x86_64 \
                     -nographic \
                     -kernel linux-X.Y.Z/arch/x86_64/boot/bzImage \
                     -append "quiet init=/hello root=PARTUUID=XXXXXXXX-01 console=ttyS0" \
                     /dev/loopXX
```
Vamos destrinchar essa chamada:

* `-kernel linux-X.Y.Z/arch/x86_64/boot/bzImage`: instrui o *QEmu* a carregar o kernel presente no caminho passado.
* `-nographic` pede para o QEmu uma sessão modo texto.
* `-append "quiet init=/hello root=PARTUUID=XXXXXXXX-01 console=ttyS0"`: estas opções são passadas para o kernel e configuram sua execução
    * `quiet`: minimiza mensagens de debug
    * `init=/hello`: aqui configuramos o primeiro programa rodado pelo nosso kernel Linux
    * `root=PARTUUID=XXXXXXXX-01`: sistema de arquivos raiz está na partição `01` do disco identificado pelo `UUID` que vocês obtiveram no `fdisk` (substitua `XXXXXXXX` pelo **Disk Identifier** anotado anteriormente sem `0x`)
    * `console-ttyS0` cria um interface de texto serial parecida com a que vocês usam em embarcados para mostrar `printf` no PC.
* `/dev/loopXX`: disco a ser colocado na máquina virtual (anotado anteriormente).

!!! example
    Adapte o comando acima para usar o disco criado por você e execute-o.

!!! tip
    No comando, na parte `root=PARTUUID=XXXXXXXX-01`, substitua `XXXXXXXX` pelo *Disk Identifier* anotado anteriormente. Se o *Disk Identifier* anotado foi `0xbd624993`, utilize `root=PARTUUID=bd624993-01`. Perceba que não utilizamos `0x`.

Se tudo der certo, você verá algo como abaixo:

```
(várias mensagens do QEMu aqui)
Hello linux maciel
[    2.636091] Kernel panic - not syncing: Attempted to kill init! exitcode=0x00000000
[    2.640952] CPU: 0 PID: 1 Comm: hello Not tainted 5.11.16 #1
[    2.641747] Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS 1.10.2-1ubuntu1 04/01/2014
(... erros continuam ...)
```

!!! example
    Procure na saída do seu QEmu o print do seu executável `hello`. Veja que o Linux carregou seu programa na memória e o executou!

!!! warning "Se algo deu errado aqui chame o professor para te ajudar a encontrar o problema."

Logo em seguida temos uma mensagem chamada *Kernel panic*. Ela acontece quando ocorre um erro irrecuperável no Linux e o sistema simplesmente para. No nosso caso o erro é *Attempted to kill init!*.

Na linha do QEmu apontamos nosso programa `hello` no parâmetro `init`. O programa apontado por `init` é especial: ele nunca termina e representa aquele `while(1)` que vocês já devem ter usado muito em embarcados. Enquanto o sistema estiver ligado o `init` está executando e "tomando conta" de todos os outros programas que estão rodando.

Bom, `init` nunca deveria terminar e o nosso termina logo após de dar um `print`. Vamos consertar isso mais para a frente.

!!! done
    Você conseguiu seu primeiro boot! Pode agora sair do QEmu digitando `Ctrl+A X`.


## Organizando os arquivos

Atualmente nosso sistema só tem um único arquivo: o executável `hello`. Claramente isso não é nem útil nem desejável. Sistemas baseados em Linux seguem uma organização (relativamente) padrão do arquivos no sistema raiz. Uma descrição formal desse padrão pode ser vista no [site da Linux Foundation](https://refspecs.linuxfoundation.org/FHS_3.0/fhs-3.0.pdf), mas vamos nos contentar lendo uma introdução breve.

!!! example
    Leia o artigo [Filesystem Hierarchy Standard](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard).

!!! warning
    A hierarquia de diretórios não representa (necessariamente) um disco físico, mas sim uma organização das informações disponíveis no sistema. Como vimos com o arquivo `raiz.img`, podemos "pendurar" o conteúdo de um disco em basicamente qualquer diretório.

Claramente nosso sistema não obedece ao padrão acima.

!!! warning
    Antes de fazer o próximo passo, lembre-se de:

    - Garantir que o `qemu` não está mais rodando.
    - Montar novamente o *device* que aponta para `raiz.img`, senão você estará criando as pastas dentro de `raiz_linux`, mas não dentro de `raiz.img`:

    <div class="termy">

    ```console
    $ sudo mount -t ext4 /dev/loopXXp1 raiz_linux
    ```

    </div>


!!! example
    Crie manualmente as pastas mostradas acima usando `mkdir`. Ao dar `ls -l` você deverá ver o seguinte:

    ```
    drwxr-xr-x 2 root root  1024 abr 30 09:46 bin
    drwxr-xr-x 2 root root  1024 abr 30 09:46 boot
    drwxr-xr-x 2 root root  1024 abr 30 09:46 dev
    drwxr-xr-x 2 root root  1024 abr 30 09:46 etc
    drwxr-xr-x 2 root root  1024 abr 30 09:46 home
    drwxr-xr-x 2 root root  1024 abr 30 09:46 lib
    drwx------ 2 root root 12288 abr 30 09:39 lost+found
    drwxr-xr-x 2 root root  1024 abr 30 09:46 proc
    drwxr-xr-x 2 root root  1024 abr 30 09:46 root
    drwxr-xr-x 2 root root  1024 abr 30 09:46 run
    drwxr-xr-x 2 root root  1024 abr 30 09:46 sbin
    drwxr-xr-x 2 root root  1024 abr 30 09:46 sys
    drwxr-xr-x 2 root root  1024 abr 30 09:46 tmp
    drwxr-xr-x 7 root root  1024 abr 30 09:46 usr
    drwxr-xr-x 2 root root  1024 abr 30 09:46 var
    ```

Uma outra parte do padrão corresponde a qual é lugar padrão do `init`. Tradicionalmente este programa está localizado no caminho `/sbin/init`. O parâmetro `init=/hello` que passamos para o Qemu sobrescreve este comportamento, porém ele não é normalmente usado em sistemas Linux.

!!! warning "Perigo real!"
    No próximo passo, quando falamos `/sbin/init`, estamos falando da raiz (`/`) do **linux da aula** que está em **raiz.img**.
    
    Cuidado para não sobrescrever o `/sbin/init` do linux da sua máquina, caso contrário não conseguirá mais fazer boot!

    Perceba que o comando de mover/renomear não terá uma barra antes de `sbin`.

!!! example "Mova com cuidado!"
    Mova `hello` para `/sbin/init` e execute novamente o Qemu, desta vez sem o parâmetro `init=...` no kernel.

    **Obs**: `init` será o novo nome do `hello`, ou seja, movemos `hello` para a pasta `sbin` do **linux da aula** e o renomeamos para `init`.

    Este passo pode ser feito com apenas um comando. Estando na pasta `raiz_linux` onde `raiz.img` está montada, faça:
    <div class="termy">

    ```console
    $ sudo mv hello sbin/init
    ```

    </div>

!!! done
    Agora que temos nosso sistema Linux minimamente funcional construído inteiramente do zero estamos prontos para começar a explorar seus recursos e possibilidades.

## Avançado

Você notou que até agora só usamos `hello`? E o que fizemos com o `hello-dyn`?

!!! example
    Tente usar `hello-dyn` no lugar de `hello` como `init`. Funciona?

Você deve perceber que nosso sistema funciona menos ainda com `hello-dyn`. Isto ocorre pois **não instalamos nenhuma das dependências** dele. Aqueles arquivos listados pelo `ldd` precisam estar disponíveis no sistema de arquivos para que ele funcione!

!!! example
    Siga os passos abaixo

    1. Faça uma lista dos arquivos necessários e de suas localizações.
    2. Copie-os para o sistema de arquivos em `raiz-linux` usando o terminal.
    3. Copie `hello-dyn` para o nosso sistema de arquivos.
    4. Inicie o qemu como `init` apontando para `hello-dyn`.

!!! done
    Pronto! Agora nosso sistema tem também as dependências básicas para rodar programas no terminal! Iremos examinar bibliotecas compartilhadas mais para a frente de novo.

<!---


Vamos agora copiar para *raiz_linux* o mínimo necessário para conseguirmos ligar nosso sistema em um prompt de comando *bash* como *root*. Várias coisas estarão faltando, mas já conseguiremos

O primeiro passo é montar a hierarquia de arquivos descrita no primeiro exercício desta seção. A lista completa pode ser vista neste link](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard).

!!! example
    Crie as pastas descritas no documento acima. Verifique que todas foram criadas rodando `ls -l` em `raiz_linux`. As pastas que você criou deverão ser as seguintes:

    ```
    drwxr-xr-x 2 root root  1024 abr 30 09:46 bin
    drwxr-xr-x 2 root root  1024 abr 30 09:46 boot
    drwxr-xr-x 2 root root  1024 abr 30 09:46 dev
    drwxr-xr-x 2 root root  1024 abr 30 09:46 etc
    drwxr-xr-x 2 root root  1024 abr 30 09:46 home
    drwxr-xr-x 2 root root  1024 abr 30 09:46 lib
    drwx------ 2 root root 12288 abr 30 09:39 lost+found
    drwxr-xr-x 2 root root  1024 abr 30 09:46 proc
    drwxr-xr-x 2 root root  1024 abr 30 09:46 root
    drwxr-xr-x 2 root root  1024 abr 30 09:46 run
    drwxr-xr-x 2 root root  1024 abr 30 09:46 sbin
    drwxr-xr-x 2 root root  1024 abr 30 09:46 sys
    drwxr-xr-x 2 root root  1024 abr 30 09:46 tmp
    drwxr-xr-x 7 root root  1024 abr 30 09:46 usr
    drwxr-xr-x 2 root root  1024 abr 30 09:46 var
    ```

!!! example
    Dê permissões totais para a pasta `tmp` e somente para o usuário dono na pasta `root`.

    ```
    #> chmod 777 tmp
    #> chmod 600 root
    ```

!!! example
    Copie seu kernel para a pasta `boot` e o executável do *busybox* para a pasta `usr/bin`.

Como vimos anteriormente, o *busybox* contém todas as ferramentas de usuário em um único executável. Porém, não é nada prático digitar *busybox* antes de **todo comando**. Por isso criaremos uma série de links simbólicos que ligam o nome de cada ferramenta oferecida pelo *busybox* ao seu nome "tradicional".


!!! example
    Execute o comando abaixo na dentro de `raiz_linux`.

    ```
    for util in $(./usr/bin/busybox --list-full); do
     ln -s /usr/bin/busybox $util
    done
    ```

!!! example
    Liste os arquivos em `raiz_linux/bin`, `raiz_linux/usr/bin` e `raiz_linux/sbin` e veja quais programas estarão disponíveis no nosso sistema.

!!! example
    Copie `hello-static` e `hello-dyn` para a pasta `raiz_linux/root`.



!!! done
    Não funcionou? Perfeito! Na próxima aula transformaremos nosso sistema capenga em um sistema mínimo e totalmente funcional.

## Inicialização do sistema - `init`

Se você explorou um pouco o sistema criado na parte anterior já deve ter notado que várias coisas não funcionam. Não conseguimos, por exemplo, escrever em nenhum arquivo. Vamos explorar dois casos mais interessantes:

!!! example
    O comando `df` (*disk free*) é usado para listar o espaço livre em todos os discos presentes no sistema. Tente executá-lo no seu sistema. O quê acontece?

!!! example
    O comando `lspci` (*list pci devices*) mostra todos os periféricos ligados diretamente na placa mãe do seu PC. Tente executá-lo no seu sistema. O quê acontece?

!!! question short
    Consulte as pastas apontadas nos itens anteriores. Elas tem conteúdo? Elas *deveriam* ter conteúdo?

Para conseguirmos testar logo, adicionamos ao kernel o parâmetro `init=/bin/sh`. Este parâmetro diz para o kernel abrir um *shell* assim que iniciar. Isto também é fonte de nossos problemas, já que nosso sistema não inicializa automaticamente nenhum serviço essencial para seu funcionamento. Ou seja, nosso sistema está capenga pois ele não possui um processo `init`, que é responsável por supervisionar a criação de todos os sistemas de arquivos especiais (`/proc, /sys, /dev/`) e por iniciar serviços essenciais para o funcionamento do sistema. Da mesma maneira, ao finalizar ele é responsável por desligar todos os recursos de hardware de maneira segura.


!!! example
    Além de ser usado para mídias removíveis, o comando `mount` também é usado para criar os diretórios especiais `/proc` e `/sys`. Rode os seguintes comandos e verifique que agora `df` e `lspci` funcionam corretamente.

    ```
    #> mount -t proc proc /proc -o nosuid,noexec,nodev
    #> mount -t sysfs sys /sys -o nosuid,noexec,nodev
    ```

!!! question short
    Qual o papel das pastas especias `/proc` e `/sys` em um sistema Linux?

Estes comandos fazem parte da inicialização normal de um sistema e expõe estruturas do kernel para o resto do sistema via arquivos. O *busybox* já nos fornece um sistema de inicialização bastante simplificado que, entre outras coisas, rodaria estes comandos automaticamente a todo boot. Aproveitaremos ele para três propósitos:

1. executar um script de inicialização que configure todos os diretórios especiais e serviços.
1. adicionar serviços que proveem uma tela de login
1. executar um script de finalização que desliga o hardware quando o PC for desligado.

Primeiro vamos copiar versões padrão de todos os arquivos de configuração necessários. Os seguintes arquivos estão na pasta `configs` do repositório da aula.

* `passwd, shadow, groups`: listam os usuários e grupos presentes. `shadows` contém hashes das senha.
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

# Parte 7 - bibliotecas e carregamento dinâmico

Quando compilamos o *busybox* habilitamos uma opção que pedia executáveis compilados estaticamente, fazendo que o executável criado não tenha dependências. Vamos agora aprender a configurar nosso sistema para rodar executáveis com dependências.

!!! example
    Copie os executáveis `hello-static` e `hello-dyn` para sua VM. Não se esqueça de adicionar permissões de execução para eles.

!!! question short
    Tente rodar ambos executáveis. Ambos funcionam? Anote abaixo o resultado da execução de cada um.

Todos os executáveis que conseguimos rodar até agora foram compilados estaticamente. Quando tentamos rodar `hello-dyn` tivemos um erro.

!!! question
    Execute (em seu sistema) `ldd` em `hello-dyn`. Anote abaixo as dependências encontradas.

!!! example
    Os arquivos acima existem na sua VM?


Ao montar nosso sistema do zero não incluimos nenhuma biblioteca! Logo, o nosso executável não consegue carregar as partes faltantes e não irá rodar. Felizmente, nosso sistema Linux possui a mesma arquitetura do Ubuntu instalado em nossas máquinas e podemos copiar os arquivos necessários para nosso sistema!


!!! example
    Copie os arquivos acima para os locais indicados na saída de `ldd`.

!!! example
    Teste novamente `hello-dyn`. Agora ele funciona?

Gerenciar **dependências** é a principal atribuição de gerenciadores de pacotes como `apt`, `pacman` e `dnf`. Eles estruturam todos os softwares instaláveis em um sistema de modo que ao instalar um programa todas as suas dependências sejam instaladas também.

!!! done
    Pronto! Agora temos um sistema mínimo e funcional. Ainda faltam vários pedaços que normalmente compõem um sistema, como um bootloader instalado na imagem de disco e um gerenciador de pacotes. Mas ao menos agora ele é plenamente funcional dentro do que propomos.
    -->
