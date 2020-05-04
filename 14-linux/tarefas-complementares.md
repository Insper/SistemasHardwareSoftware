% 14 e 15 - linux do zero
% Igor dos Santos Montagner

# Tarefas complementares

1. Atualmente o `QEmu` carrega nosso kernel via linha de comando. Apesar de isto ser prático nenhuma arquitetura faz este processo desta maneira. Pesquise o quê é um *boot loader* e como instalar o [Grub2](https://www.gnu.org/software/grub/manual/grub/grub.html) em seu sistema.
2. Crie um novo usuário usando `adduser`, logue usando ele e verifique que ele possui uma pasta no diretório `/home`.
3. Nosso sistema está contido inteiramente em uma só partição do disco. Isto dificulta a migração para novas versões de um sistema pois mistura os arquivos de usuário (pasta `/home`) e de configurações do sistema. Crie uma nova partição no seu disco de tamanho *20Mb* e faça seu sistema utilizá-la para o diretório `/home`. Para isto você precisará redimensionar a partição atual para *80Mb* e editar o arquivo `/etc/fstab` para montar sua nova partição no diretório `/home` ao inicializar o sistema.
