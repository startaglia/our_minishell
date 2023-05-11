#include "minishell.h"

void    split_readline(t_shell *shell)
{
    int     i;
    t_list *token;

    token = (t_list *)malloc(1 * sizeof(t_list));
    shell->splitted_pipe = ft_split(shell->pipeline);
}