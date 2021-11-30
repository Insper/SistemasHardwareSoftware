#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

// Esta versão usa realloc e consegue ler linhas de tamanho indefinido.
char *proxima_linha(int fd) {

    int n=2;
    char buf;
    char *linha = malloc(sizeof(char)*n);

    int bytes_read = 0;
    int i=0;
    do {
        bytes_read = read(fd, &buf, 1);
        if (bytes_read > 0 && buf!='\n') {
            if (i==n) {
                n = n * 2;
                linha = realloc(linha, sizeof(char)*n);
            }
            linha[i] = buf;
            i++;
        }
    } while (bytes_read > 0 && buf!='\n');
    
    if (i==0) {
        return NULL;
    }

    linha[i]='\0';

    return linha;
}


int main() {

    int fd = open("alice.txt", O_RDONLY);
    
    // Vamos tentar ler 10 linhas?! Será que temos tudo isso?
    for (int i=0; i<10; i++) {
        printf("%dª Linha: %s\n", i+1, proxima_linha(fd));
    }

    return 0;
}
