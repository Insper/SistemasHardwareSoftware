#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 10000

/* Recebe duas strings e concatena em uma terceira */
char *mystrcat(char *str1, char *str2) {

}

int main(int argc, char *argv[]) {
    char str1[MAX_STR], str2[MAX_STR];
    char *strres;

    printf("Informe uma frase qualquer: \n");
    fgets(str1, MAX_STR, stdin);

    printf("Informe uma frase qualquer: \n");
    fgets(str2, MAX_STR, stdin);

    strres = mystrcat(str1, str2);

    printf("\nFrase 1 original....: %s\n", str1);
    printf("Frase 2 original....: %s\n", str2);
    printf("Frase concatenada...: %s\n", strres);

    return 0;
}
