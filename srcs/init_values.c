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
    return (0);  
}

int	init_values(t_shell *shell)
{
    if (init_mem(shell))
        return (1);
    return (0);
}