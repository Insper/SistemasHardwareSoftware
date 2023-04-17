#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char words[5][20] = {"lascar", "idiota", "lascou", "vagabundo", "safado"};

    char *token = strtok(argv[1], " \n");

    while (token != NULL)
    {
        printf("Analisando... \"%s\"\n", token);
        sleep(1);
        for (int i=0; i<5; i++) {
            if (strcmp(words[i], token) == 0) {
                return 1;
            }
        }
        token = strtok(NULL, " \n");
    }

    return 0;
}