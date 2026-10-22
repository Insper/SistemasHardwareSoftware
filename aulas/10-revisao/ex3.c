#include <stdio.h>

int v_global = 10;

int func1(int n) {
    int x = 10;
    return x + n;
}

int func2(int n) {
    return v_global + n;
}

int func3(int n, int mult) {
    return v_global + n * mult;
}

void func4() {
    int aux = func1(5);
    if (aux > 20) {
        printf("O novo valor eh maior que 20");
    } else {
        printf("O novo valor nao eh maior que 20");
    }
}

int main() {
    return 0;
}