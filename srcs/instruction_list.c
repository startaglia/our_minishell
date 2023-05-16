#include "minishell.h"

void    create_instruction_list(t_shell *shell)
{
    int     i;


    shell->token = (t_node *)malloc(sizeof(t_node));
    shell->token = ft_lstnew((char*)shell->splitted_pipe[0]);
    i = 1;
    while (shell->splitted_pipe[i])
    {    
        ft_lstadd_back(&shell->token, ft_lstnew((char *)shell->splitted_pipe[i]));
        shell->token = shell->token->next;
        i++;
    }
}