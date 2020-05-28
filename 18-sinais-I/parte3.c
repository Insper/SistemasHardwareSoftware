#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

int main()
{
    pid_t filho = fork();
    if (filho == 0)
    {
        printf("%d\n", getpid());
        return 5;
        while (1)
        {
        }
    }
    sleep(10);
    int st;
    pid_t filho_acabou = waitpid(filho, &st, WNOHANG);
    if (filho_acabou == 0) {
        kill(filho, SIGKILL);
        wait(&st);
    }    
    
    if (WIFSIGNALED(st))
        printf("%s\n", strsignal(WTERMSIG(st)));
    if (WIFEXITED(st))
        printf("Return: %d\n", WEXITSTATUS(st));

    return 0;
}