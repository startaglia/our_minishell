# include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
    t_shell shell;

    (void)argc;
    (void)argv;
    (void)envp;
    init_prompt(&shell, envp);
    return (0);
}
