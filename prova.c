#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    char *path = argv[1];
    //printf("%s\n", argv[1]);
    argv++;
    if (execve(path, argv, envp) == -1)
        printf("Oh no\n");
}