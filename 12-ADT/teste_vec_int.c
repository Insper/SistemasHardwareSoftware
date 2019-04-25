#include "mintest/macros.h"
#include "vec_int.h"
#include <stdlib.h>

// estah aqui para podermos testar o capacity
typedef struct _vec_int {
    int *data;
    int size;
    int capacity;
} vec_int;

int test_creation_destroy() {
    

    vec_int *vec = vec_int_create();
    test_assert(vec != NULL, "create retornou NULL!");
    
    test_assert(vec->capacity == 1, "Capacidade começa diferente de 1!");

    test_assert(vec_int_size(vec) == 0, "Tamanho inicial diferente de 0!");
    
    int i;
    test_assert(vec_int_get(vec, 0, &i) == 0, "Retornou 1 em posição inválida!");
    vec_int_destroy(&vec);
    test_assert(vec == NULL, "vec não foi setado como null apos destroy!");

    return 1;
}


int test_push_pop() {
    

    vec_int *vec = vec_int_create();
    test_assert(vec != NULL, "create retornou NULL!");
    vec_int_push(vec, 10);

    int v;
    test_assert(vec_int_get(vec, 0, &v), "Retornou 0 com elemento que existe!");
    test_assert(v==10, "get não retornou valor correto!");

    vec_int_push(vec, 20);
    vec_int_push(vec, 30);
    vec_int_push(vec, 40);
    vec_int_push(vec, 80);

    test_assert(vec->capacity == 8, "Capacidade diferente de 8 após 4 push!");

    test_assert(vec_int_size(vec) == 5, "Tamanho diferente de 4 apos 4 push!");
    test_assert(vec_int_get(vec, 2, &v), "Retornou 0 em elemento que existe!");
    test_assert(v == 30, "get(2) diferente de 30!");

    test_assert(vec_int_pop(vec) == 80, "pop retornou valor diferente do último!");
    test_assert(vec_int_size(vec) == 4, "Tamanho diferente de 3 apos 4 push e 1 pop!");
    
    vec_int_pop(vec);
    vec_int_pop(vec);
    vec_int_pop(vec);
    vec_int_pop(vec);

    test_assert(vec_int_size(vec) == 0, "Retornou size diferente de 0!");
    test_assert(vec_int_pop(vec) == 0, "Retornou valor diferente de 0 ao fazer pop no vetor vazio!");
    
    vec_int_destroy(&vec);

    return 1;
}

int test_insert() {
    

    vec_int *vec = vec_int_create();
    test_assert(vec != NULL, "create retornou NULL!");

    vec_int_push(vec, 10);
    vec_int_push(vec, 30);
    vec_int_push(vec, 40);
    vec_int_push(vec, 60);
    vec_int_push(vec, 70);

    vec_int_insert(vec, 1, 20);
    
    int val;
    test_assert(vec_int_get(vec, 1, &val) != 0, "Retornou 0 em elemento existente!");
    test_assert(val == 20, "Elemento adicionado diferente de 20!");

    test_assert(vec_int_get(vec, 2, &val) != 0, "Retornou 0 em elemento existente!");
    test_assert(val == 30, "Elemento adicionado diferente de 30!");

    test_assert(vec_int_get(vec, 5, &val) != 0, "Retornou 0 em elemento existente!");
    test_assert(val == 70, "Elemento adicionado diferente de 70!");

    vec_int_insert(vec, 4, 50);

    for (int i = 1; i <= 7; i++) {
        test_assert(vec_int_get(vec, (i-1), &val) != 0, "Retornou 0 em elemento existente!");
        test_assert(val == i*10, "Elemento não confere!");

    }

    vec_int_destroy(&vec);
    return 1;
}

int test_remove() {
    
    
    vec_int *vec = vec_int_create();
    test_assert(vec != NULL, "create retornou NULL!");

    vec_int_push(vec, 1000);
    vec_int_push(vec, 10);
    vec_int_push(vec, 20);
    vec_int_push(vec, 30);
    vec_int_push(vec, 40);
    vec_int_push(vec, 50);

    vec_int_remove(vec, 0);

    int val;
    for (int i = 1; i <= 5; i++) {
        test_assert(vec_int_get(vec, (i-1), &val) != 0, "Retornou 0 em elemento existente!");
        test_assert(val == i*10, "Elemento não confere!");
    }
    

    vec_int_destroy(&vec);
    return 1;
}

int test_capacity() {
    
    
    vec_int *vec = vec_int_create();
    test_assert(vec != NULL, "create retornou NULL!");

    vec_int_push(vec, 1000);
    test_assert(vec->capacity == 2, "Capacidade não aumentou!");

    vec_int_push(vec, 1000);
    vec_int_push(vec, 1000);
    vec_int_push(vec, 1000);
    test_assert(vec->capacity == 8, "Capacidade não aumentou!");
    vec_int_push(vec, 1000);

    vec_int_pop(vec);
    vec_int_pop(vec);
    vec_int_pop(vec);
    test_assert(vec->capacity == 4, "Capacidade não diminuiu!");

    vec_int_insert(vec, 0, 3);
    vec_int_insert(vec, 3, 5);
    test_assert(vec->capacity == 8, "Capacidade não aumentou!");

    vec_int_destroy(&vec);
    return 1;
}

test_list = {TEST(test_creation_destroy), TEST(test_push_pop), TEST(test_insert), TEST(test_remove), TEST(test_capacity)};
#include "mintest/runner.h"
