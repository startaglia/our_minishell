#include "../../includes/minishell.h"

int ft_cd(char **command)
{
    if (chdir(command[1]) == -1)
        perror("Failed cd");
    return (0);
}