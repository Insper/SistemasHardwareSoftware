# Linux: Instalação e configuração 

## Download e particionar

Para fazer o download do Linux Ubuntu 22.04.5 LTS acesse o link [https://releases.ubuntu.com/jammy/](https://releases.ubuntu.com/jammy/), e [nesse VÍDEO](https://www.youtube.com/watch?v=VK4eCi7ktCE) explica como fazer dual boot de uma máquina com Windows e Linux.

## Usando WSL
Uma outra opção é usar Subsistema do Windows para Linux (WSL) que permite que os desenvolvedores instalem uma distribuição do Linux (como Ubuntu, OpenSUSE, Kali, Debian, Arch Linux etc) e usem aplicativos Linux, utilitários e ferramentas de linha de comando bash diretamente no Windows, sem modificação, sem a sobrecarga de uma máquina virtual tradicional.

Siga os passos de instalação no documento [Instalação do WSL+Ubuntu no Windows](WSL_Windows_Ubuntu_VSCode.pdf). Para saber mais acesse [esse LINK](https://learn.microsoft.com/pt-br/windows/wsl/install) para configurar VSCode+WSL acesse [esse LINK](https://code.visualstudio.com/docs/remote/wsl).


## VM usando Virtualbox

### Shared Folder

Uma boa maneira de transferir arquivos entre a VM e a máquina hospedeira (ambas as direções) é criar uma pasta compartilhada no Virtualbox.

Acesse [este LINK](https://carleton.ca/scs/tech-support/troubleshooting-guides/creating-a-shared-folder-in-virtualbox/) para mais informações!

### Shared Clipboard

Também é possível fazer com que algo copiado (CTRL + C) no sistema principal possa ser colado no Ubuntu (CTRL + V na máquina Virtual), e vice-versa!

Procure no Google `virtualbox enable shared clipboard`.