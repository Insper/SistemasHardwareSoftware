#include <stdio.h>

/* 
 * O tipo union faz com que duas variáveis compartilhem o 
 * mesmo espaço de memória. Assim, tanto num.i quanto num.f
 * se referem aos mesmos bytes na memória. Porém, ao acessar
 * num.i eles são interpretados como int e ao acessar num.f 
 * eles são interpretados como float.
 *
 * Usamos isto para mostrar os bytes que compõem o número 
 * 5.75 usado na aula passada. Note que isto é sua interpretação
 * como int, não os bytes efetivamente guardados na memória. 
 */
typedef union {
    int i;
    float f;
} int_ou_float;

int main() {
    int_ou_float num;
    num.f = 5.75;
    
    /* 
     * %x mostra um número em hexa
     */
    printf("%#08x\n", num.i);
    
    return 0;
}
