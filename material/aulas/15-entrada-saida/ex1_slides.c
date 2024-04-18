// para compilar: gcc -g ex1_slides.c -o ex1_slides
// para consultar open use: man 2 open
/* POSIX headers */
#include <fcntl.h>  /*open */
#include <unistd.h> /*read, close */

/* Standard C */
#include <stdio.h>

int main () {
    int fd;
    char c;
    // abre o arquivo, retorna -1 
    // se o arquivo não existir
    fd = open("entrada.txt", O_RDONLY);
    // le um caractere do arquivo
    read(fd,&c,1);
    
    printf("c = %c\n", c);
    // Fechar um arquivo informa ao kernel 
    // que você já terminou de acessar 
    // o arquivo. SEMPRE FAÇA ISSO.
    close(fd);
    return 0;
}
