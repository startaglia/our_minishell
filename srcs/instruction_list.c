#include "minishell.h"

static int  get_execve_arg_len(t_shell *shell)
{
    int     i;
    t_node  *temp;

    temp = shell->token;
    i = 0;
    while (temp->next)
    {
        // if (!ft_strncmp(temp->command, "<", 1) || !ft_strncmp(temp->command, ">", 1)
        //     || !ft_strncmp(temp->command, "|", 1))
        // {
        //     temp = temp->prev;
        //     i--;
        //     break ;
        // }
        // else if (!ft_strncmp(temp->command, ">>", 2) ||
        //     !ft_strncmp(temp->command, "<<", 2))
        // {
        //     temp = temp->prev;
        //     i--;
        //     break ;
        // }
        // else
        // {
            i++;
            temp = temp->next;
        // }
    }
    return (i);
}

static char    **create_execve_arg(t_shell *shell)
{
    char    **ret;
    int     ret_len;
    int     i;
    t_node  *temp;

    i = 0;
    temp = shell->token;
    ret_len = get_execve_arg_len(shell) + 1;
    ret = (char**)malloc(sizeof(char*) * ret_len);
    if (ret_len == 1)
    {
        ret[0] = temp->command;
        ret[1] = NULL;
        return (ret);
    }
    else
    {
        while (i < ret_len)
        {
            ret[i] = temp->command;
            i++;
            temp = temp->next;
        }
    }
    ret[i] = NULL;
    return (ret);
}

void    create_instruction_list(t_shell *shell)
{
    int     i;

    shell->token = ft_lstnew((char*)shell->splitted_pipe[0]);
    i = 1;
    while (shell->splitted_pipe[i])
    {
        ft_lstadd_back(&shell->token, ft_lstnew((char *)shell->splitted_pipe[i]));
        shell->token = shell->token->next;
        i++;
    }
    if (shell->token->prev)
    {
        while (shell->token->prev)
            shell->token = shell->token->prev;
    }
    shell->execve_arg = create_execve_arg(shell);
}