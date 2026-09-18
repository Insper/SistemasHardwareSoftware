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
    int fd1 = open(arq1, O_WRONLY | O_CREAT, 0700);
    for (int i = 0; i < 10; i++) {
        buf[0] = '0' + i;
        write(fd1, buf, 1);
        //sleep(2); // só está aqui para facilitar nossa visualização. Tirar para os exercícios
    }
    close(fd1);

    return 0;
}
