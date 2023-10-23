// para compilar: gcc -g ex2_slides.c -o ex2_slides
/* POSIX headers */
#include <fcntl.h>  /*open */
#include <unistd.h> /*read, close */

/* Standard C */
#include <stdio.h>

int main () {
    int fd1,fd2;
    char c;
    fd1 = open("entrada.txt", O_RDONLY);
    fd2 = open("entrada.txt", O_RDONLY);
    
    read(fd1,&c,1);
    printf("c1 = %c\n", c);
    
    read(fd2,&c,1);
    printf("c2 = %c\n", c);
    
    close(fd1);
    close(fd2);
    return 0;
}
