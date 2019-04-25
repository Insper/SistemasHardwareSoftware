#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long arg1 = atol(argv[1]);

    if (arg1 < 0) return -1;
    return arg1 % 2 == 0;
}
