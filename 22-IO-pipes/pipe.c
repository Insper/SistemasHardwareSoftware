#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void func1() {
    sleep(1);
    printf("print(\"Este e um comando python!\", 1, 2, 4//3, 4/3)\n");
}

void func2() {
    // complete aqui com exec
}


int main() {
    // crie o pipe e redireciona a saída do processo pai para
    // a entrada do filho ;)

    pid_t f = fork();

    if (f != 0) {
        func1();
    } else {
        func2();
    }
}