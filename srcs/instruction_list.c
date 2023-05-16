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
    while (shell->token->prev)
        shell->token = shell->token->prev;
}

static int  get_execve_arg_len(t_shell *shell)
{
    int     i;

    i = 0;
    while (shell->token->next)
    {
        if (!ft_strncmp(shell->token->command, "<", 1) || !ft_strncmp(shell->token->command, ">", 1)
            || !ft_strncmp(shell->token->command, "|", 1))
        {
            shell->token = shell->token->prev;
            break ;
        }
        else if (!ft_strncmp(shell->token->command, ">>", 2) ||
            !ft_strncmp(shell->token->command, "<<", 2))
        {
            shell->token = shell->token->prev;
            break ;
        }
        else
        {
            i++;
            shell->token = shell->token->next;
        }
    }
    while (shell->token->prev)
        shell->token = shell->token->prev;
    return (i);
}

char    **create_execve_arg(t_shell *shell)
{
    char    **ret;
    int     ret_len;
    int     i;

    i = 0;
    ret_len = get_execve_arg_len(shell) + 1;
    ret = (char**)malloc(sizeof(char*) * ret_len);
    while (i < ret_len)
    {
        ret[i] = shell->token->command;
        printf("%s\n");
        i++;
        shell->token = shell->token->next;
    }
    while (shell->token->prev)
        shell->token = shell->token->prev;
    ret[i] = NULL;
    return (ret);
}