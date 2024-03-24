#include <stdio.h>

void func1(unsigned short *vec) {
    vec[0] = 0;
    vec[1] = 10;
    vec[2] = 20;
}

void func2(int *vec, int n) {
    for (int i = 0; i < n; i++) {
        vec[i] = i * 10;
    }
}