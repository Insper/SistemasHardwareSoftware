#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
    char arq1[100], arq2[100];
    int fd1, fd2, bytes_read;
    char buf[1];

    scanf("%s", arq1);
    scanf("%s", arq2);
    
    fd1 = open(arq1, O_RDONLY);
    fd2 = open(arq2, O_WRONLY | O_CREAT, 0700);
    
    do {
        bytes_read = read(fd1, buf, 1); // le um byte de arq1
        if (bytes_read > 0) {
            write(fd2, buf, 1); // escreve um byte em arq2
        }
    } while (bytes_read != 0);
    
    close(fd1);
    close(fd2);
    
    return 0;

}
