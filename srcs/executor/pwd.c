#include "../../includes/minishell.h"

int ft_pwd()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return (0);
}