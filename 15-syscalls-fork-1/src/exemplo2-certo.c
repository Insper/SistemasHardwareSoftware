#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t filho;

    filho = fork();

    if (filho == 0) {
        sleep(1); // cooloquei soh para ficar facil de ver o resultado!
        printf("Acabei filho\n");
        return 2;
    } else {
        int child_status;
        wait(&child_status);
        if (WIFEXITED(child_status)) {
            printf("O valor de retorno foi: %d\n", WEXITSTATUS(child_status));
        } else {
            printf("Algum erro estranho ocorreu!\n");
        }
    }
    return 0;
}
