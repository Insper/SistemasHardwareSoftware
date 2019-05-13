
#define _GNU_SOURCE

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


void funcao_lenta() {
    for (int i = 0; i < 5; i++) {
        printf("Filho %d", i);
        sleep(2);
        printf(" -- Fim Filho %d\n", i);
    }
}

void funcao_lenta_pai() {
    for (int i = 0; i < 10; i++) {
        printf("Pai %d", i);
        sleep(1);
        printf(" -- Fim Pai %d\n", i);
    }
}

int main(int argc, char *argv[]) {
    int fdtemp = open("/tmp", O_TMPFILE | O_RDWR, 0600);
    if (fork() != 0) {
        funcao_lenta_pai();
    } else {
        dup2(fdtemp, 1);
        funcao_lenta();
        exit(0);
    }
    
    wait(NULL);
    
    lseek(fdtemp, SEEK_SET, 0);
    char c;
    while (read(fdtemp, &c, 1) > 0) {
        write(1, &c, 1);
    }
    
    return 0;
}
