#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

int main()
{
    if (fork() == 0)
    {
        printf("%d\n", getpid());
        while (1)
        {
        }
    }
    int st;
    wait(&st);
    if (WIFSIGNALED(st))
        printf("%s\n", strsignal(WTERMSIG(st)));
    if (WIFEXITED(st))
        printf("Return: %d\n", WEXITSTATUS(st));

    return 0;
}