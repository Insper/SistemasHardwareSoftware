#include <stdlib.h>

#include "vec_int.h"

typedef struct _vec_int {
    int *data;
    int size;
    int capacity;
} vec_int;


// cria um novo vec_int usando malloc.
vec_int *vec_int_create() {
    vec_int *v = NULL;
    // alocar memoria aqui

    v->size = 0;
    v->capacity = 0; // o que voce colocaria aqui?
    
    return v;
}

void vec_int_destroy(vec_int **_v) {
    // libera a memória usada por v e seta v = NULL;
}

int vec_int_size(vec_int *v) {
    return v->size;
}

void vec_int_push(vec_int *v, int i) {
    // e se o array encher?
    // e se estiver vazio?
    
    v->data[v->size] = i;
    v->size++;
}

int vec_int_get(vec_int *v, int pos, int *vi) {
    if (pos >= 0 && pos < v->size) {
        *vi = v->data[pos];
        return 1;
    }
    return 0;
}

int vec_int_pop(vec_int *v) {
    // e se estiver vazio?
    
    int i = 0;
    vec_int_get(v, v->size - 1, &i);
    v->size--;
    
    // e se o array ficar muito vazio?
    
    return i;
}

void vec_int_insert(vec_int *v, int pos, int val) {
    // fazer realocacao de memoria!
    // o que ocorre se o array encher?
    
    for (int i = v->size; i > pos; i--) {
        v->data[i] = v->data[i-1];
    }
    v->data[pos] = val;
    v->size++;
}

void vec_int_remove(vec_int *v, int pos) {
    // fazer realocacao de memoria!
    // o que ocorre se o array ficar muito vazio?

    for (int i = pos; i < v->size; i++) {
        v->data[i] = v->data[i+1];
    }
    v->size--;
    
}
