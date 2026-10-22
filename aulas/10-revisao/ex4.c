#include <stdio.h>

int ex4() {
    unsigned short n;

    scanf("%hu", &n);

    int res = 0;
    int i = 1;
    
    while (i < n) {
        res += (i*4);
        i++;
    }

    return res;
}

int main() {
    return 0;
}