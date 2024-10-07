// stack.h
typedef struct {
    int capacity;  
    int *data;
    int size;
}stack_int;

stack_int * stack_int_new(int capacity);
void stack_int_delete(stack_int *_s);
int stack_int_empty(stack_int *s);
int stack_int_full(stack_int *s);
void stack_int_push(stack_int *s, int value);
int stack_int_pop(stack_int *s);