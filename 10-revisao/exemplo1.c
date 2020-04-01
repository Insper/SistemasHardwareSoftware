#include <stdio.h>

int var_global = 10;

void muda_valor(int a, int b, int *c) {
    var_global++;
    *c = a + 3*b;
    var_global += *c * 3;
}

int main() {
    int b;
    muda_valor(1, 2, &b);
}
