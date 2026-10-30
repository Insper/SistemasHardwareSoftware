// test_stack.c
// gcc -Og -Wall -g test_stack.c stack.o -o teste_stack
#include <stdio.h>
#include "stack.h"

int main() {
    // Cria um stack com capacidade para 5 elementos
    stack_int *s = stack_int_new(5);  

    stack_int_push(s, 10);
    stack_int_push(s, 20);
    stack_int_push(s, 30);
    // Remove o topo: 30
    printf("Valor removido: %d\n", stack_int_pop(s)); 
    // Remove o topo: 20
    printf("Valor removido: %d\n", stack_int_pop(s));
    stack_int_delete(s);  // Libera a memória

    return 0;
}