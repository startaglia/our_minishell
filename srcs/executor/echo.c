#include "../../includes/minishell.h"

int ft_echo(char **command)
{
    int i;

    i = 1;
    if (ft_strncmp(command[1], "-n", 2) == 0)
        i++;
    while (command[i])
    {
        printf("%s", command[i]);
        if (command[i + 1])
            printf(" ");
        i++;
    }
    // printf("%s\n", command[1]);
    if (ft_strncmp(command[1], "-n", 2) == 0)
        return (0);
    else
        printf("\n");
    return (0);
}