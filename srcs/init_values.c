/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:30:10 by startagl          #+#    #+#             */
/*   Updated: 2023/05/11 12:01:59 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int init_ops(t_shell *shell)
// {
//     int i;

//     i = 0;
//     while (shell->node)
//     {
//         /* code */
//     }
    
//     shell->node->operators
// }

int	init_mem(t_shell *shell)
{
	shell = (t_shell *) malloc(sizeof(t_shell));
        if (!shell)
            return (1); 
    shell->node = (t_node *)malloc(sizeof(t_node));
       if (!shell->node)
            return (1);
    shell->node->operators = (t_operators *)malloc(sizeof(t_operators));
        if (!shell->node->operators)
            return (1);
    //shell->node->operators->pipe = false;
    return (0);  
}

int	init_values(t_shell *shell, char **env)
{
    if (init_mem(shell))
    {
        shell->sng_pipe = false;
        shell->sng_heredoc = false;
        shell->sng_redir = false;
        shell->sng_in = false;
        shell->sng_append = false;
        shell->copy_env = env;
        return (1);
    }
    shell->sng_pipe = false;
    if (!shell->sng_heredoc)
        shell->sng_heredoc = false;
    if (!shell->sng_redir)
        shell->sng_redir = false;
    if (!shell->sng_in)
        shell->sng_in = false;
    if (!shell->sng_append)
        shell->sng_append = false;
    shell->copy_env = env;
    return (0);
}