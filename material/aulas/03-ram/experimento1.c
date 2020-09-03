#include <stdio.h>

void show_bytes(unsigned char *ptr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%02x ", ptr[i]);  
    }
    printf("\n");
}

int main() {
    float f = 5.75;
    
    /* 
     * a macro sizeof retorna o tamanho, em bytes, de um tipo
     *
     * sizeof(float) == 4
     *
     * mandamos mostrar os bytes **guardados na memória**.
     */
    printf("Valor guardado na memória para f=%f : ", f);
    show_bytes((unsigned char *) &f, sizeof(f));
    
    
    int i = 0x11223344;
    printf("Valor guardado na memória para i=%d : ", i);
    show_bytes((unsigned char *) &i, sizeof(i));
    
    return 0;
}
