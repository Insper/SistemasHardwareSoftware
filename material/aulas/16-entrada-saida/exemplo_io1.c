/* POSIX headers */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Standard C */
#include <stdio.h>

int main (int argc, char *argv[]) {
    char arq1[100]; // nomes do arquivo, recebido via scanf
    char buf[1]; // local usado para guardar os dados lidos de arq1
    
    scanf("%s", arq1);
    int fd1 = open(arq1, O_RDONLY);
    for (int i = 0; i < 5; i++) {
        read(fd1, buf, 1);
        printf("Caracter lido: %c\n", buf[0]);
    }
    close(fd1);
    
    return 0;
}
