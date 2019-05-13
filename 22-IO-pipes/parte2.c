#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <unistd.h>
#include <stdio.h>


int main() {
    int fds[2];
    
    pipe(fds);
    
    if (fork()) {
        int j;
        close(fds[1]);
        read(fds[0], &j, sizeof(int));
        printf("%d\n", j);
    } else {
        int i = 10;
        close(fds[0]);
        write(fds[1], &i, sizeof(int));
    }
    
    return 0;
}
