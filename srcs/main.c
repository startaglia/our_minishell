#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
    t_shell shell;
    // int     i;

    (void)argc;
    (void)argv;
    // (void)envp;
    // i = 0;
    // while (envp[i])
    // {
    //     printf("%d\t%s\n", i, envp[i]);
    //     i++;
    // }
    init_prompt(&shell, envp);
    return (0);
}
