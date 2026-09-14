#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main () {
    pid_t f1, f2;
    int counter = 3;

    f1 = fork();
    if (f1 == 0){
        counter++;
    }

    f2 = fork();
    if (f2) {
        counter *= 2;
    }
    if (f1 && !f2) {
        counter--;
    }
    printf("f1 %d f2 %d counter %d\n", f1, f2, counter);

    if (f2) wait(NULL);


    printf("fim %d\n", getpid());

    return 0;
}
