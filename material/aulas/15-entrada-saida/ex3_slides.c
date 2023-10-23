// para compilar: gcc -g ex3_slides.c -o ex3_slides
/* POSIX headers */
#include <fcntl.h>  /*open */
#include <unistd.h> /*read, close */

/* Standard C */
#include <stdio.h>

int main () {
    int fd;
    char c;
    fd = open("entrada.txt", O_RDONLY);
    if(fork()==0){
        read(fd,&c,1);
        printf("c filho = %c\n", c);
    }else{
        read(fd,&c,1);
        printf("c pai = %c\n", c);
    }
    close(fd);
    return 0;
}
