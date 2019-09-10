#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 10000

char *mystrcpy(char *stroriginal) {

}

int main(int argc, char *argv[]) {
    char stroriginal[MAX_STR];
    char *strcopia;

    printf("Informe uma frase qualquer: \n");
    fgets(stroriginal, MAX_STR, stdin);

    strcopia = mystrcpy(stroriginal);

    printf("\nFrase original....: %s\n", stroriginal);
    printf("Frase copia.......: %s\n", strcopia);
    
    return 0;
}
