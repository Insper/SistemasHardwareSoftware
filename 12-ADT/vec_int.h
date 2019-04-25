
struct _vec_int;

typedef struct _vec_int vec_int;

// cria um novo vec_int usando malloc.
vec_int *vec_int_create();
// libera a memória usada por v e seta v = NULL;
void vec_int_destroy(vec_int **v); //
int vec_int_size(vec_int *v); // devolve o tamanho do vetor.
void vec_int_push(vec_int *v, int i); // adiciona i ao fim do vetor
// retorna posição pos do vetor na variavel apontada por vi .
// retorna 1 se a posição pos está preenchida e 0 caso contrário.
int vec_int_get(vec_int *v, int pos, int *vi);
// retorna o último elemento do vetor e o remove.
int vec_int_pop(vec_int *v);
// insere i na posição pos. Se pos >= tamanho adiciona
// no fim
void vec_int_insert(vec_int *v, int pos, int i);
// remove o elemento na posição pos. Se pos >= tamanho
// não faz nada.
void vec_int_remove(vec_int *v, int pos);

